#pragma once
#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <sstream>

class RegistryEditor {
public:
    RegistryEditor(HKEY rootKey, const std::string& subKey) : rootKey(rootKey) {
        if (RegOpenKeyExA(rootKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
            throw std::runtime_error("Failed to open registry key.");
        }
    }

    ~RegistryEditor() {
        if (hKey != NULL) {
            RegCloseKey(hKey);
        }
    }

    template<typename T>
    void setValue(const std::string& name, const T& value) {
        DWORD type = getRegType(value);
        LONG result = RegSetValueExA(hKey, name.c_str(), 0, type, reinterpret_cast<const BYTE*>(&value), sizeof(value));
        if (result != ERROR_SUCCESS) {
            throw std::runtime_error("Failed to set registry value.");
        }
    }

    template<typename T>
    T getValue(const std::string& name) {
        T value;
        DWORD type;
        DWORD dataSize = sizeof(value);
        LONG result = RegQueryValueExA(hKey, name.c_str(), nullptr, &type, reinterpret_cast<LPBYTE>(&value), &dataSize);
        if (result != ERROR_SUCCESS) {
            throw std::runtime_error("Failed to get registry value.");
        }
        return value;
    }

    void deleteValue(const std::string& name) {
        LONG result = RegDeleteValueA(hKey, name.c_str());
        if (result != ERROR_SUCCESS) {
            throw std::runtime_error("Failed to delete registry value.");
        }
    }

    void deleteKey(const std::string& subKey) {
        LONG result = RegDeleteKeyA(rootKey, subKey.c_str());
        if (result != ERROR_SUCCESS) {
            throw std::runtime_error("Failed to delete registry key.");
        }
    }

private:
    HKEY rootKey;
    HKEY hKey;

    DWORD getRegType(const std::string&) const { return REG_SZ; }
    DWORD getRegType(DWORD) const { return REG_DWORD; }
};
