#pragma once
#include "1_triangle/lve_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace lve{
	class LVEModel	{
	public:

		struct Vertex{
			glm::vec2 position;
			glm::vec3 color;
			static std::vector<VkVertexInputBindingDescription> get_binding_descriptions(); 
			static std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions(); 
		};
		

		LVEModel(LVEDevice& device, const std::vector<Vertex> &vertices);
		~LVEModel();
		LVEModel(const LVEModel&) = delete;
		LVEModel &operator=(const LVEModel&) = delete;

		void bind(VkCommandBuffer command_buffer);
		void draw(VkCommandBuffer command_buffer);

	private:
		LVEDevice &_lve_device;
		VkBuffer _vertex_buffer;
		VkDeviceMemory _vertex_buffer_memory;
		uint32_t  _vertex_count;

		void createVertexBuffers(const std::vector<Vertex> &vertices);


		
	};
	

	
}