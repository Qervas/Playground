#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include <memory>
#include <vector>
namespace lve{
	class Triangle{

		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;

			Triangle();
			~Triangle();

			Triangle(const LVEWindow&) = delete;
			Triangle operator=(const LVEWindow&) = delete;
			void run();

		private:
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void drawFrame();

			LVEWindow _lve_window{WIDTH, HEIGHT, "Hello World!"};
			LVEDevice _lve_device{_lve_window};
			LVESwapChain _lve_swap_chain{_lve_device, _lve_window.getExtent()};
			std::unique_ptr<LVEPipeline> _lve_pipeline;
			VkPipelineLayout _pipeline_layout;
			std::vector<VkCommandBuffer> _command_buffer;
			
	};
};