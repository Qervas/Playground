#include "1_triangle/triangle.hpp"
#include <stdexcept>

namespace lve{
	Triangle::Triangle(){
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	Triangle::~Triangle(){
		vkDestroyPipelineLayout(_lve_device.device(), _pipeline_layout, nullptr);
		// vkDestroyPipeline(_lve_device.device(), _lve_pipeline, nullptr);
	}
	
	void Triangle::run(){
		while(!_lve_window.shouldClose()){
			glfwPollEvents();
		}
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

	}

	void Triangle::drawFrame(){

	}
};