#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include "1_triangle/lve_model.hpp"


#include <memory>
#include <vector>
namespace lve{
	class Triangle{

		public:
			static constexpr int WIDTH = 1920;
			static constexpr int HEIGHT = 1440;

			Triangle();
			~Triangle();

			Triangle(const LVEWindow&) = delete;
			Triangle operator=(const LVEWindow&) = delete;
			void run();

		private:
			void loadModels();
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void drawFrame();

			void sierpinski(std::vector<LVEModel::Vertex> &vertices,
							int depth,
							glm::vec2 left,
							glm::vec2 right,
							glm::vec2 top);

			LVEWindow _lve_window{WIDTH, HEIGHT, "Hello World!"};
			LVEDevice _lve_device{_lve_window};
			LVESwapChain _lve_swap_chain{_lve_device, _lve_window.getExtent()};
			std::unique_ptr<LVEPipeline> _lve_pipeline;
			VkPipelineLayout _pipeline_layout;
			std::vector<VkCommandBuffer> _command_buffer;
			std::unique_ptr<LVEModel> _lve_model;
			
	};
};