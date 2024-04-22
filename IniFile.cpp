#include "IniFile.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

IniFile::IniFile(const std::string& path) : filePath(path) {
	ifstream file(filePath);

	if (file.is_open()) {
		string line;
		string currentSection;
		while (getline(file, line)) {

			cleanupStr(line);

			size_t lpos = line.find('[');
			size_t rpos = line.find(']');
			
			if (line.empty()) {
				continue;
			}
			if (lpos != string::npos && lpos != line.rfind('[')) {
				continue;
			}
			if (rpos != string::npos && rpos != line.rfind(']')) {
				continue;
			}
			if (lpos != string::npos && rpos == string::npos) {
				continue;
			}

			if (lpos != string::npos && rpos != string::npos) {
				currentSection = line.substr(1, line.length() - 2);
			}
			if (currentSection.empty()) {
				continue;
			}

			size_t pos = line.find('=');

			if (pos != string::npos && (pos == line.rfind('='))) {

				string key = line.substr(0, pos); 
				string value = line.substr(pos + 1);

				cleanupStr(key);
				cleanupStr(value);

				if (key.empty() || value.empty()) {
					continue;
				}

				data[currentSection][key] = value;
			} 
		}
		file.close();
	}
}

IniFile::~IniFile() {
	save();
}

void IniFile::cleanupStr(std::string& str) {
	size_t kom = str.find(';');
	if (kom != string::npos) {
		str = str.substr(0, kom);
	}

	size_t start = str.find_first_not_of(' ');
	size_t end = str.find_last_not_of(' ');

	if (start == string::npos || end == string::npos) {
		str.clear();
	} else {
		str = str.substr(start, end - start + 1);
	}
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

	if (isKeysExist(section, key)) {
		return stoi(data[section][key]);
	}

	return def;
}

double IniFile::readDouble(const std::string& section, const std::string& key, double def) {

	if (isKeysExist(section, key)) {
		return stod(data[section][key]);
	}
	return def;
}

std::string IniFile::readString(const std::string& section, const std::string& key, const std::string& def) {

	if (isKeysExist(section, key)) {
		return data[section][key];
	}
	return def;
}

bool IniFile::readBool(const std::string& section, const std::string& key, bool def) {

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

	return def;
}	

void IniFile::writeInt(const std::string& section, const std::string& key, int value) {
	data[section][key] = to_string(value);
}

void IniFile::writeDouble(const std::string& section, const std::string& key, double value) {
	data[section][key] = to_string(value);
}

void IniFile::writeString(const std::string& section, const std::string& key, const std::string& value) {
	data[section][key] = value;
}

void IniFile::writeBool(const std::string& section, const std::string& key, bool value) {
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
	return data[section].count(key);
}

size_t IniFile::getSectionsCount() {
	size_t res = 0;
	for (const auto& section : data) {
		if (!section.second.empty()) {
			res++;
		}
	}
	return res;
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