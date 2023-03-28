#include "1_triangle/lve_pipeline.hpp"
#include <fstream>
#include <iostream>
namespace lve{

	LVEPipeline::LVEPipeline(const std::string& vert_file_path, const std::string& frag_file_path){
		createGraphicsPipeline(vert_file_path, frag_file_path);
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


	void LVEPipeline::createGraphicsPipeline(const std::string& vert_file_path, const std::string& frag_file_path){
		
		auto vert_code = readFile(vert_file_path);
		auto frag_code = readFile(frag_file_path);

		std::cout << "vert: " << vert_code.size() << "\n" << "frag: " << frag_code.size() << std::endl;
	}
};