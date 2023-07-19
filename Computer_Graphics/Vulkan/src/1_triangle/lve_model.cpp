#include "1_triangle/lve_model.hpp"

#include <cassert>
#include <cstring>



namespace lve{

LVEModel::LVEModel(LVEDevice &device, const std::vector<Vertex> &vertices):_lve_device{device}{
	createVertexBuffers(vertices);
}

LVEModel::~LVEModel(){
	vkDestroyBuffer(_lve_device.device(), _vertex_buffer, nullptr);
	vkFreeMemory(_lve_device.device(), _vertex_buffer_memory, nullptr);
}

void LVEModel::createVertexBuffers(const std::vector<Vertex> &vertices){
	_vertex_count = static_cast<uint32_t>(vertices.size());
	assert(_vertex_count >= 3 && "Vertex count must be at least 3");
	VkDeviceSize buffer_size = sizeof(vertices[0]) * _vertex_count;
	_lve_device.createBuffer(buffer_size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
							 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
							 _vertex_buffer,
							 _vertex_buffer_memory);

	void *data;
	vkMapMemory(_lve_device.device(), _vertex_buffer_memory, 0, buffer_size, 0, &data);
	memcpy(data, vertices.data(), static_cast<size_t>(buffer_size));
	vkUnmapMemory(_lve_device.device(), _vertex_buffer_memory);
}


void LVEModel::bind(VkCommandBuffer command_buffer){
	VkBuffer buffers[] = {_vertex_buffer};
	VkDeviceSize offsets[] = {0};
	vkCmdBindVertexBuffers(command_buffer, 0, 1, buffers, offsets);
}

void LVEModel::draw(VkCommandBuffer command_buffer){
	vkCmdDraw(command_buffer, _vertex_count, 1, 0, 0);
}

std::vector<VkVertexInputBindingDescription> LVEModel::Vertex::get_binding_descriptions(){
	std::vector<VkVertexInputBindingDescription> binding_descriptions(1);
	binding_descriptions[0].binding = 0;
	binding_descriptions[0].stride = sizeof(Vertex);
	binding_descriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return binding_descriptions;
}

std::vector<VkVertexInputAttributeDescription> LVEModel::Vertex::get_attribute_descriptions(){
	std::vector<VkVertexInputAttributeDescription> attribute_descriptions(2);
	attribute_descriptions[0].binding = 0;
	attribute_descriptions[0].location = 0;
	attribute_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attribute_descriptions[0].offset = offsetof(Vertex, position);

	attribute_descriptions[1].binding = 0;
	attribute_descriptions[1].location = 1;
	attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attribute_descriptions[1].offset = offsetof(Vertex, color );
	return attribute_descriptions;
}

}


