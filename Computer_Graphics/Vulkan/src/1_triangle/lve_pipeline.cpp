#include "1_triangle/lve_pipeline.hpp"
#include <fstream>
#include <iostream>
#include <cassert>
namespace lve{

	LVEPipeline::LVEPipeline(LVEDevice &device,
				const std::string& vert_file_path,
				const std::string& frag_file_path,
				const PipelineConfigInfo& config_info): _lve_device(device){
		
		createGraphicsPipeline(vert_file_path, frag_file_path, config_info);
	}

	LVEPipeline::~LVEPipeline(){
		vkDestroyShaderModule(_lve_device.device(), _vert_shader_module, nullptr);
		vkDestroyShaderModule(_lve_device.device(), _frag_shader_module, nullptr);
		vkDestroyPipeline(_lve_device.device(),_graphics_pipeline, nullptr);
		// vkDestroyDevice(_lve_device.device(), nullptr);
	}

	std::vector<char> LVEPipeline::readFile(const std::string& file_path){
		std::ifstream file{file_path, std::ios::ate | std::ios::binary};

		if(!file.is_open()){
			throw std::runtime_error("failed to open file" + file_path);
		}

		size_t file_size = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(file_size);

		file.seekg(0);
		file.read(buffer.data(), file_size);
		file.close();
		return buffer;
	}


	void LVEPipeline::createGraphicsPipeline(const std::string& vert_file_path,
											 const std::string& frag_file_path,
											 const PipelineConfigInfo& config_info){
		
		assert(config_info.pipeline_layout ==  VK_NULL_HANDLE && "Cannot create graphics pipeline: no pipelineLayout provided n config_info");
		assert(config_info.render_pass ==  VK_NULL_HANDLE && "Cannot create graphics pipeline: no renderpass provided n config_info");
		auto vert_code = readFile(vert_file_path);
		auto frag_code = readFile(frag_file_path);

		createShaderModule(vert_code, &_vert_shader_module);
		createShaderModule(frag_code, &_frag_shader_module);

		VkPipelineShaderStageCreateInfo shader_stages[2];
		shader_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shader_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shader_stages[0].module = _vert_shader_module;
		shader_stages[0].pName = "main";
		shader_stages[0].flags = 0;
		shader_stages[0].pNext = nullptr;
		shader_stages[0].pSpecializationInfo = nullptr;

		shader_stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shader_stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shader_stages[1].module = _frag_shader_module;
		shader_stages[1].pName = "main";
		shader_stages[1].flags = 0;
		shader_stages[1].pNext = nullptr;
		shader_stages[1].pSpecializationInfo = nullptr;

		VkPipelineVertexInputStateCreateInfo vertex_input_info{};
		vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_info.vertexAttributeDescriptionCount = 0; // no vertex attributes
		vertex_input_info.vertexBindingDescriptionCount = 0; // no vertex bindings
		vertex_input_info.pVertexAttributeDescriptions = nullptr; // no vertex attributes
		vertex_input_info.pVertexBindingDescriptions = nullptr; // no vertex bindings

		VkPipelineViewportStateCreateInfo viewport_info{};
		viewport_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_info.viewportCount = 1;//viewport means the area of the framebuffer that will be rendered to
		viewport_info.pViewports = &config_info.viewport;
		viewport_info.scissorCount = 1;
		viewport_info.pScissors = &config_info.scissor;

		VkGraphicsPipelineCreateInfo pipeline_info{};
		pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline_info.stageCount = 2;
		pipeline_info.pStages = shader_stages;
		pipeline_info.pVertexInputState = &vertex_input_info;
		pipeline_info.pInputAssemblyState = &config_info.input_assembly_info;
		pipeline_info.pViewportState = &viewport_info;
		pipeline_info.pRasterizationState = &config_info.rasterizer_info;
		pipeline_info.pMultisampleState = &config_info.multisampling_info;
		pipeline_info.pColorBlendState = &config_info.color_blending_info;
		pipeline_info.pDepthStencilState = &config_info.depth_stenci_info;

		pipeline_info.pDynamicState = nullptr;

		pipeline_info.layout = config_info.pipeline_layout;
		pipeline_info.renderPass = config_info.render_pass;
		pipeline_info.subpass = config_info.subpass;

		pipeline_info.basePipelineIndex = -1;
		pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

		if(vkCreateGraphicsPipelines(_lve_device.device(), VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &_graphics_pipeline) != VK_SUCCESS){
			throw std::runtime_error("failed to create graphics pipelines :)");
		}



	}

	void LVEPipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shader_module){
		VkShaderModuleCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		create_info.codeSize = code.size();
		create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());//not C style array

		if(vkCreateShaderModule(_lve_device.device(), &create_info, nullptr, shader_module) != VK_SUCCESS){
			throw std::runtime_error("failed to create shader module :)");
		}
	}

	PipelineConfigInfo LVEPipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height){
		PipelineConfigInfo config_info{};
		config_info.input_assembly_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		config_info.input_assembly_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		config_info.input_assembly_info.primitiveRestartEnable = VK_FALSE;

		config_info.viewport.x = 0.0f;
		config_info.viewport.y = 0.0f;
		config_info.viewport.width = static_cast<float>(width);
		config_info.viewport.height = static_cast<float>(height);
		config_info.viewport.minDepth = 0.0f;
		config_info.viewport.maxDepth = 1.0f;//linearly transform Z component of the vertex position

		config_info.scissor.offset = {0, 0};
		config_info.scissor.extent = {width, height};//scissor means the area of the framebuffer that will be affected by the rasterizer



		config_info.rasterizer_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		config_info.rasterizer_info.depthClampEnable = VK_FALSE;//depth clamp means if the fragment is beyond the near and far plane, clamp it to the near and far plane
		config_info.rasterizer_info.rasterizerDiscardEnable = VK_FALSE;//if true, geometry never passes through the rasterizer stage
		config_info.rasterizer_info.polygonMode = VK_POLYGON_MODE_FILL;//fill, edge, point
		config_info.rasterizer_info.lineWidth = 1.0f;//line width
		config_info.rasterizer_info.cullMode = VK_CULL_MODE_NONE;
		config_info.rasterizer_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;//clockwise or counter clockwise
		config_info.rasterizer_info.depthBiasEnable = VK_FALSE;//depth bias means if the fragment is behind the other fragment, offset the depth value
		config_info.rasterizer_info.depthBiasConstantFactor = 0.0f;// means the constant factor of the depth bias
		config_info.rasterizer_info.depthBiasClamp = 0.0f;//means the maximum depth bias
		config_info.rasterizer_info.depthBiasSlopeFactor = 0.0f;//means the slope factor of the depth bias

		config_info.multisampling_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		config_info.multisampling_info.sampleShadingEnable = VK_FALSE;
		config_info.multisampling_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		config_info.multisampling_info.minSampleShading = 1.0f;
		config_info.multisampling_info.pSampleMask = nullptr;
		config_info.multisampling_info.alphaToCoverageEnable = VK_FALSE;
		config_info.multisampling_info.alphaToOneEnable = VK_FALSE;

		config_info.color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
														 VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		config_info.color_blend_attachment.blendEnable = VK_FALSE;
		config_info.color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		config_info.color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		config_info.color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
		config_info.color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		config_info.color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		config_info.color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

		config_info.color_blending_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		config_info.color_blending_info.logicOpEnable = VK_FALSE;
		config_info.color_blending_info.logicOp = VK_LOGIC_OP_COPY;
		config_info.color_blending_info.attachmentCount = 1;
		config_info.color_blending_info.pAttachments = &config_info.color_blend_attachment;
		config_info.color_blending_info.blendConstants[0] = 0.0f;
		config_info.color_blending_info.blendConstants[1] = 0.0f;
		config_info.color_blending_info.blendConstants[2] = 0.0f;
		config_info.color_blending_info.blendConstants[3] = 0.0f;

		config_info.depth_stenci_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		config_info.depth_stenci_info.depthTestEnable = VK_TRUE;
		config_info.depth_stenci_info.depthWriteEnable = VK_TRUE;
		config_info.depth_stenci_info.depthCompareOp = VK_COMPARE_OP_LESS;
		config_info.depth_stenci_info.depthBoundsTestEnable = VK_FALSE;
		config_info.depth_stenci_info.minDepthBounds = 0.0f;
		config_info.depth_stenci_info.maxDepthBounds = 1.0f;
		config_info.depth_stenci_info.stencilTestEnable = VK_FALSE;
		config_info.depth_stenci_info.front = {};
		config_info.depth_stenci_info.back = {};




		

		return config_info;
	}
};