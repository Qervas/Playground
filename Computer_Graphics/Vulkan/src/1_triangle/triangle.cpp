#include "1_triangle/triangle.hpp"


#include <stdexcept>
#include <array>

namespace lve{
	Triangle::Triangle(){
		loadModels();
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	Triangle::~Triangle(){
		vkDestroyPipelineLayout(_lve_device.device(), _pipeline_layout, nullptr);
	}
	
	void Triangle::run(){
		while(!_lve_window.shouldClose()){
			glfwPollEvents();
			drawFrame();
		}

		vkDeviceWaitIdle(_lve_device.device());

	}

	void Triangle::sierpinski(std::vector<LVEModel::Vertex> &vertices,
								int depth,
								glm::vec2 left,
								glm::vec2 right,
								glm::vec2 top){

		  if (depth <= 0) {
			vertices.push_back({top});
			vertices.push_back({right});
			vertices.push_back({left});
		} else {
			auto leftTop = 0.5f * (left + top);
			auto rightTop = 0.5f * (right + top);
			auto leftRight = 0.5f * (left + right);
			sierpinski(vertices, depth - 1, left, leftRight, leftTop);
			sierpinski(vertices, depth - 1, leftRight, right, rightTop);
			sierpinski(vertices, depth - 1, leftTop, rightTop, top);
		}
	}

	void Triangle::loadModels(){
		std::vector<LVEModel::Vertex> vertices{};
		sierpinski(vertices, 10, {-0.5f, 0.5f}, {0.5f, 0.5f}, {0.0f, -0.5f});
		_lve_model = std::make_unique<LVEModel>(_lve_device, vertices);
	}

	void Triangle::createPipelineLayout(){
		VkPipelineLayoutCreateInfo pipeline_layout_info{};
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.setLayoutCount = 0;
		pipeline_layout_info.pSetLayouts = nullptr;
		pipeline_layout_info.pushConstantRangeCount = 0;
		pipeline_layout_info.pPushConstantRanges = nullptr;
		if(vkCreatePipelineLayout(_lve_device.device(), &pipeline_layout_info, nullptr, &_pipeline_layout)
			!= VK_SUCCESS){
				throw std::runtime_error("failed to crete pipeline layout :)");
		}

	}

	void Triangle::createPipeline(){
		auto pipeline_config = LVEPipeline::defaultPipelineConfigInfo(_lve_swap_chain.width(), _lve_swap_chain.height());
		pipeline_config.render_pass = _lve_swap_chain.getRenderPass();
		pipeline_config.pipeline_layout = _pipeline_layout;
		_lve_pipeline = std::make_unique<LVEPipeline>(_lve_device, 
														"build/shaders/1_triangle/default.vert.spv",
														"build/shaders/1_triangle/default.frag.spv",
														pipeline_config);			

	}

	void Triangle::createCommandBuffers(){
		_command_buffer.resize(_lve_swap_chain.imageCount());
		VkCommandBufferAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		alloc_info.commandPool = _lve_device.getCommandPool();
		alloc_info.commandBufferCount = static_cast<uint32_t>(_command_buffer.size());

		if(VK_SUCCESS != vkAllocateCommandBuffers(_lve_device.device(), &alloc_info, _command_buffer.data())){
			throw std::runtime_error("failed to allocate command buffers!");
		}

		for( int i = 0; i < _command_buffer.size(); i++){
			VkCommandBufferBeginInfo begin_info{};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if(vkBeginCommandBuffer(_command_buffer[i], &begin_info)){
				throw std::runtime_error("failed to begin recording command buffer!");
			}

			VkRenderPassBeginInfo render_pass_info{};
			render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			render_pass_info.renderPass = _lve_swap_chain.getRenderPass();
			render_pass_info.framebuffer = _lve_swap_chain.getFrameBuffer(i);

			render_pass_info.renderArea.offset = {0, 0};
			render_pass_info.renderArea.extent = _lve_swap_chain.getSwapChainExtent();

			std::array<VkClearValue, 2> clear_value{};
			clear_value[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
			clear_value[1].depthStencil = {1.0f, 0};
			render_pass_info.clearValueCount = static_cast<uint32_t>(clear_value.size());
			render_pass_info.pClearValues = clear_value.data();

			vkCmdBeginRenderPass(_command_buffer[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

			_lve_pipeline->bind(_command_buffer[i]);
			_lve_model->bind(_command_buffer[i]);
			_lve_model->draw(_command_buffer[i]);
			//// vkCmdDraw(_command_buffer[i], 3, 1, 0, 0);	
			//// vkCmdEndRenderPass(_command_buffer[i]);

			if( VK_SUCCESS != vkEndCommandBuffer(_command_buffer[i])){
				throw std::runtime_error("failed to record command buffer");
			}
		}
	}

	void Triangle::drawFrame(){
		uint32_t image_index;
		auto result = _lve_swap_chain.acquireNextImage(&image_index);

		if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
			throw std::runtime_error("failed to acquire swap chain  image!");
		}

		result = _lve_swap_chain.submitCommandBuffers(&_command_buffer[image_index], &image_index);
		if(result != VK_SUCCESS){
			throw std::runtime_error("failed to present swap chain image!");
		}

	}
};