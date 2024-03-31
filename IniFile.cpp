#include <IniFile.h>
using namespace std;

IniFile::IniFile(const std::string& path) : filePath(path) {
	ifstream file(filePath);

	if (file.is_open()) {
		string line;
		string currentSection;
		while (getline(file, line)) {
			if (line.empty() || line[0] == ';') {
				continue;
			}
			if (line[0] == '[' && line[line.size() - 1] == ']') {
				currentSection = line.substr(1, line.size() - 2);
			}
			size_t pos = line.find('=');
			if (pos != string::npos) {
				string key = line.substr(0, pos);
				string value = line.substr(pos + 1);

				data[currentSection][key] = value;
			}
		}
		file.close();
	}
}

IniFile::~IniFile() {

}

void IniFile::save() {
	ofstream file(filePath);

	if (file.is_open) {
		for (const auto& section : data) {
			file << "[" << section.first << "]" << enld;;
		}
	}
	else {

	}
}

int IniFile::readInt(const std::string& section, const std::string& key, int def = 0) {

}

double IniFile::readDouble(const std::string& section, const std::string& key, double def = 0) {

}

std::string IniFile::readString(const std::string& section, const std::string& key, const std::string& def = "") {

}

bool IniFile::readBool(const std::string& section, const std::string& key, bool def = false) {

}

void IniFile::writeInt(const std::string& section, const std::string& key, int value) {

}

void IniFile::writeDouble(const std::string& section, const std::string& key, double value) {

}

void IniFile::writeString(const std::string& section, const std::string& key, const std::string& value) {

}

void IniFile::writeBool(const std::string& section, const std::string& key, bool value) {

}

bool IniFile::isSectionExist(const std::string& section) {

}

bool IniFile::isKeysExist(const std::string& section, const std::string& key) {

}

size_t IniFile::getSectionsCount() {

}

size_t IniFile::getKeysCount(const std::string& section) {

}

SectionsMap IniFile::getSections() const {

}

bool IniFile::deleteSection(const std::string& section) {

}

bool IniFile::deleteKey(const std::string& section, const std::string& key) {

}

bool IniFile::addNewSection(const std::string& section) {

}