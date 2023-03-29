#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include <filesystem>
namespace lve{
	class Triangle{

		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;
			std::string prefix = "build/shaders/1_triangle/";

			Triangle();
			~Triangle()=default;
			void run();

		private:
			LVEWindow _lve_window{WIDTH, HEIGHT, "Hello World!"};
			LVEDevice _lve_device{_lve_window};
			LVEPipeline lve_pipeline{ _lve_device,
									prefix + "default.vert.spv",
									prefix + "default.frag.spv",
									LVEPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};
};