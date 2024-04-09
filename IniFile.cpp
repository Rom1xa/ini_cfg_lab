#include "IniFile.h"
#include <stdexcept>

using namespace std;

IniFile::IniFile(const std::string& path) : filePath(path) {
	ifstream file(filePath);

	if (file.is_open()) {
		string str;
		string currentSection;
		while (getline(file, str)) {
			string line = cleanupStr(str);

			size_t lpos = line.find('[');
			size_t rpos = line.find(']');
			
			if (line.empty()) {
				continue;
			}
			if (lpos != string::npos && lpos != line.rfind('[')) {
				currentSection = "";
				continue;
			}
			if (rpos != string::npos && rpos != line.rfind(']')) {
				currentSection = "";
				continue;
			}

			if (lpos != string::npos) {
				currentSection = line.substr(1, line.length() - 2);
			}
			if (currentSection.empty()) {
				continue;
			}

			size_t pos = line.find('=');
			if (pos != string::npos && (pos == line.rfind('='))) {
				string key = line.substr(0, pos);
				string value = line.substr(pos + 1);
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

std::string IniFile::cleanupStr(std::string str) {
	string temp = "";

	for (char c : str) {
		if (c == ';') {
			return temp;
		}
		if (c != ' ') {
			temp += c;
		}
	}
	return temp;
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