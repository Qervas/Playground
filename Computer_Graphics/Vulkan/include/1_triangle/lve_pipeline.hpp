#pragma once

#include "1_triangle/lve_device.hpp"
#include <string>
#include <vector>
namespace lve{

	struct PipelineConfigInfo{
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineInputAssemblyStateCreateInfo input_assembly_info;
		VkPipelineRasterizationStateCreateInfo rasterizer_info;
		VkPipelineMultisampleStateCreateInfo multisampling_info;
		VkPipelineColorBlendAttachmentState color_blend_attachment;
		VkPipelineColorBlendStateCreateInfo color_blending_info;
		VkPipelineDepthStencilStateCreateInfo depth_stenci_info;
		VkPipelineLayout pipeline_layout = nullptr;
		VkRenderPass render_pass = nullptr;
		uint32_t subpass = 0;

	};


	class LVEPipeline{
		public:
			LVEPipeline(LVEDevice &device,
						const std::string& vert_file_path,
						const std::string& frag_file_path,
						const PipelineConfigInfo& config_info);
			~LVEPipeline();

			LVEPipeline(const LVEPipeline&) = delete;
			void operator=(const LVEPipeline&) = delete;

			void bind(VkCommandBuffer command_buffer);

			static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

		private:

			static std::vector<char> readFile(const std::string& file_path);
			void createGraphicsPipeline(const std::string& vert_file_path,
										const std::string& frag_file_path,
										const PipelineConfigInfo& config_info);

			void createShaderModule(const std::vector<char>& code, VkShaderModule* shader_module);


			LVEDevice& _lve_device;
			VkPipeline _graphics_pipeline;
			VkShaderModule _vert_shader_module;
			VkShaderModule _frag_shader_module;
	};
};