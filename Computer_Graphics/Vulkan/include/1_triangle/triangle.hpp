#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
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
			LVEWindow lve_window{WIDTH, HEIGHT, "Hello World!"};
			LVEPipeline lve_pipeline{prefix + "default.vert.spv", prefix + "default.frag.spv"};
	};
};