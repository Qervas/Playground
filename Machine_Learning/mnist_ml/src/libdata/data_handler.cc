#include "data_handler.hpp"

data_handler::data_handler(){
	data_array = new std::vector<data * >;
	training_data = new std::vector<data * >;
	test_data = new std::vector<data * >;
	validation_data = new std::vector<data * >;
}

data_handler::~data_handler(){

}

void data_handler::read_feature_vector(const std::string& path){
	uint32_t header[4];
	unsigned char bytes[4];
	FILE *f = fopen(path.c_str(), "r");
	if(f){
		for(int i = 0; i < 4; i++){
			if(fread(bytes, sizeof(bytes), 1, f)){ // successfully read 4 bytes
				header[i] = convert_to_little_endian(bytes);
			}else{
				throw std::runtime_error("Error reading file");
			}
		}
		printf("Done getting input file header.\n");
		int image_size = header[2] * header[3];
		for(int i = 0; i < header[1]; i++){
			data *d = new data();
			uint8_t element[1];
			for(int j = 0; j < image_size; j++){
				if(fread(element, sizeof(element), 1, f)){
					d->append_to_feature_vector(element[0]);
				}else{
					throw std::runtime_error("Error reading file");
				}
			}
			data_array->emplace_back(d);
		}
		printf("Successfully read and stored %lu feature vectors.\n", data_array->size());
	}else{
		throw std::runtime_error("Error opening file");
	}

}

void data_handler::read_feature_labels(const std::string& path){
	uint32_t header[2];
	unsigned char bytes[4];
	FILE *f = fopen(path.c_str(), "r");
	if(f){
		for(int i = 0; i < 2; i++){
			if(fread(bytes, sizeof(bytes), 1, f)){ // successfully read 2 bytes
				header[i] = convert_to_little_endian(bytes);
			}else{
				throw std::runtime_error("Error reading file");
			}
		}
		printf("Done getting Label File Header.\n");
		for(int i = 0; i < header[1]; i++){
			uint8_t element[1];
			if(fread(element, sizeof(element), 1, f)){
				data_array->at(i)->set_label(element[0]);
			}else{
				throw std::runtime_error("Error reading file");
			}
		}
		printf("Successfully read and stored label.\n");
	}else{
		throw std::runtime_error("Error opening file");
	}

}
void data_handler::split_data(){
	std::unordered_set<int> used_indexes;
	int train_size = data_array->size() * TRAIN_SET_PERCENT;
	int test_size = data_array->size() * TEST_SET_PERCENT;
	int validation_size = data_array->size() * VALIDATION_PERCENT;

	//Training data
	int count = 0;
	while(count < train_size){
		int rand_index = rand() % data_array->size();
		if(used_indexes.find(rand_index) == used_indexes.end()){
			training_data->emplace_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
			count++;
		}
	}
	
	//Test data
	count = 0;
	while(count < test_size){
		int rand_index = rand() % data_array->size();
		if(used_indexes.find(rand_index) == used_indexes.end()){
			test_data->emplace_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
			count++;
		}
	}

	//Validation data
	count = 0;
	while(count < validation_size){
		int rand_index = rand() % data_array->size();
		if(used_indexes.find(rand_index) == used_indexes.end()){
			validation_data->emplace_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
			count++;
		}
	}

	printf("Training Data Size: %lu\n", training_data->size());
	printf("Test Data Size: %lu\n", test_data->size());
	printf("Validation Data Size: %lu\n", validation_data->size());
}
void data_handler::count_classes(){
	int count = 0;
	for(unsigned i = 0; i < data_array->size(); i++){
		if(class_map.find(data_array->at(i)->get_label()) == class_map.end()){
			class_map[data_array->at(i)->get_label()] = count;
			data_array->at(i)->set_enumerated_label(count);
			count++;
		}
	}
	num_classes = count;
	printf("Successfully Extracted %d Unique Classes.\n", num_classes);
}

uint32_t data_handler::convert_to_little_endian(const unsigned char* bytes){
	return (uint32_t)bytes[0] << 24 | (uint32_t)bytes[1] << 16 | (uint32_t)bytes[2] << 8 | (uint32_t)bytes[3];
}

std::vector<data* > * data_handler::get_training_data(){
	return training_data;
}
std::vector<data* > * data_handler::get_test_data(){
	return test_data;
}
std::vector<data* > * data_handler::get_validation_data(){
	return validation_data;
}

