#include "maxqueue.h"
#include <algorithm>

/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author Maria Gallego Siles y Juan Reche Aguilar
*/


MaxQueue::MaxQueue() {}
MaxQueue::~MaxQueue() {}

//mal
void MaxQueue::push(int value) {

	int maxval = elements_.empty() ? value : std::max(value, elements_.front().max_value );

	//faltaba & son punteros preguntarlo bien
	for (auto& i:elements_) {
		i.max_value = maxval;
	}

	elements_.push_back({value, maxval});
}

void MaxQueue::pop() {

	if (elements_.empty()) {
		throw std::out_of_range("ERROR (pop): La cola está vacía.");
	}
	elements_.pop_front();

	//miramos el nuevo maximo
	/**
	 * ideas:
	 * max_element con un funtor y luego cambiar max_value a todo
	 * buscar con for
	*/
	if( !elements_.empty()) {

		// auto maxE = std::max_element(elements_.begin(), elements_.end(), compare_elemet);
		// int new_max = maxE->value;
		//
		// for (auto& i: elements_) {
		// 	i.max_value = new_max;
		// }

		int new_max = elements_.front().value;
		for (const auto& el : elements_) {
			new_max = std::max(new_max, el.value);
		}
		for (auto& el : elements_) {
			el.max_value = new_max;
		}
	}
}

element MaxQueue::front() {
	return elements_.front();
}

int MaxQueue::max() {
	return elements_.front().max_value;
}

int MaxQueue::size() {
	return elements_.size();
}

bool MaxQueue::empty() {
	return elements_.empty();
}

std::ostream& operator<<(std::ostream& os, const element& elem) {
	os << elem.value << ", " << elem.max_value;
	return os;
}

bool compare_elemet(const element& i_element, const element& j_element){
	return i_element.value < j_element.value;
}