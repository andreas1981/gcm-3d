NumericalMethod::NumericalMethod() { logger = NULL; };

NumericalMethod::~NumericalMethod() { };

void NumericalMethod::attach(Logger* new_logger) { logger = new_logger; };

int NumericalMethod::do_next_part_step(Node* cur_node, Node* new_node, float time_step, int stage)
{
	if(logger != NULL)
		logger->write(string("ERROR: Called unimplemented next part step calculation!"));
	return -1;
};

int NumericalMethod::get_number_of_stages() { return -1; };
