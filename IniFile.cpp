#include "IniFile.h"
#include <stdexcept>

using namespace std;

IniFile::IniFile(const std::string& path) : filePath(path) {
	ifstream file(filePath);

	if (file.is_open()) {
		string line;
		string currentSection;
		while (getline(file, line)) {
			size_t kpos = line.find(';');
			size_t ppos = line.find(']');
			size_t tpos = line.find(' ');
			if (line.empty() || line[0] == ';') {
				continue;
			}
			// if (line[0] == '[' && line[line.size() - 1] == ']') {
			// 	currentSection = line.substr(1, line.size() - 2);
			// }
			if (line[0] == '[') {
				currentSection = line.substr(1, ppos - 1);
			}
			size_t pos = line.find('=');
			if (pos != string::npos) {
				string key = line.substr(0, pos);
				string value = "";
				string temp = line.substr(pos + 1, kpos - pos - 1);
				for(char c : temp) if (c != ' ') value += c;

				data[currentSection][key] = value;
			} else {
				data[currentSection] = KeysMap();
			}
		}
		file.close();
	}
}

IniFile::~IniFile() {
	save();
}

void IniFile::save() {
	ofstream file(filePath);

	if (file.is_open()) {
		for (const auto& section : data) {
			file << "[" << section.first << "]" << endl;
			for (const auto& key : section.second) {
				file << key.first << "=" << key.second << endl;
			}
		}
		file.close();
	}
	else {
		cerr << "unable to save configuration" << endl;
	}
}

int IniFile::readInt(const std::string& section, const std::string& key, int def) {

	// if (!isSectionExist(section)) {
	// 	addNewSection(section);
	// }
	// if (!isKeysExist(section, key)) {
	// 	writeInt(section, key, def);
	// }
	if (isKeysExist(section, key)) {
		return stoi(data[section][key]);
	}

	return def;
}

double IniFile::readDouble(const std::string& section, const std::string& key, double def) {
	// if (!isSectionExist(section)) {
	// 	addNewSection(section);
	// }
	// if (!isKeysExist(section, key)) {
	// 	writeDouble(section, key, def);
	// }
	if (isKeysExist(section, key)) {
		return stod(data[section][key]);
	}
	return def;
}

std::string IniFile::readString(const std::string& section, const std::string& key, const std::string& def) {
	// if (!isSectionExist(section)) {
	// 	addNewSection(section);
	// }
	// if (!isKeysExist(section, key)) {
	// 	writeString(section, key, def);
	// }
	if (isKeysExist(section, key)) {
		return data[section][key];
	}
	return def;
}

bool IniFile::readBool(const std::string& section, const std::string& key, bool def) {
	// if (!isSectionExist(section)) {
	// 	addNewSection(section);
	// }
	// if (!isKeysExist(section, key)) {
	// 	writeBool(section, key, def);
	// }
	if (isKeysExist(section, key)) {
		for (auto& value : trueValues) {
			if (data[section][key] == value) {
				return true;
			}
		}
		for (auto& value : falseValues) {
			if (data[section][key] == value) {
				return false;
			}
		}
	}
	//throw std::invalid_argument("invalid bool argument");
	return def;
}	

void IniFile::writeInt(const std::string& section, const std::string& key, int value) {
	// if (!isSectionExist(section)) {
	// 	addNewSection(section);
	// }
	data[section][key] = to_string(value);
}

void IniFile::writeDouble(const std::string& section, const std::string& key, double value) {
	// if (!isSectionExist(section)) {
	// 	addNewSection(section);
	// }
	data[section][key] = to_string(value);
}

void IniFile::writeString(const std::string& section, const std::string& key, const std::string& value) {
	// if (!isSectionExist(section)) {
	// 	addNewSection(section);
	// }
	data[section][key] = value;
}

void IniFile::writeBool(const std::string& section, const std::string& key, bool value) {
	// if (!isSectionExist(section)) {
	// 	addNewSection(section);
	// }
	if (value) {
		data[section][key] = "true";
	} else {
		data[section][key] = "false";
	}
}

bool IniFile::isSectionExist(const std::string& section) {
	return data.count(section);
}

bool IniFile::isKeysExist(const std::string& section, const std::string& key) {
	// data.count(section) && 
	return data[section].count(key);
}

size_t IniFile::getSectionsCount() {
	size_t res = 0;
	for (const auto& section : data) {
		if (!section.first.empty()) {
			res++;
		}
	}
	return res;
	// return data.size();
}

size_t IniFile::getKeysCount(const std::string& section) {
	return data[section].size();
}

SectionsMap IniFile::getSections() const {
	return data;
}

bool IniFile::deleteSection(const std::string& section) {
	return data.erase(section);
}

bool IniFile::deleteKey(const std::string& section, const std::string& key) {
	return data[section].erase(key);
}

bool IniFile::addNewSection(const std::string& section) {
	if (!data.count(section)) {
		data[section] = KeysMap();
		return true;
	}
	return false;
}