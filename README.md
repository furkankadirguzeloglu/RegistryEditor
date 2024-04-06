# Logger

A simplified Registry Editor library

## Features

- Provides a simple interface for interacting with the Windows Registry.
- Allows setting, getting, and deleting registry keys and values.
- Supports setting and getting values of different types, including strings and integers.
- Automatically handles error cases, throwing exceptions when registry operations fail.

## Usage 
```cpp
#include "RegistryEditor.hpp"

int main() {
    try {
        RegistryEditor regEditor(HKEY_CURRENT_USER, "Software\\MyApp");

        // SetValue
        regEditor.setValue("TestString", std::string("Hello, Registry!"));
        regEditor.setValue("TestInteger", DWORD(42));

        // GetValue
        std::cout << "TestString: " << regEditor.getValue<std::string>("TestString") << std::endl;
        std::cout << "TestInteger: " << regEditor.getValue<DWORD>("TestInteger") << std::endl;

        // DeleteValue
        regEditor.deleteValue("TestString");
        regEditor.deleteValue("TestInteger");
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
```

## License
This project is licensed under the terms of the MIT license. See the [LICENSE](https://raw.githubusercontent.com/furkankadirguzeloglu/RegistryEditor/main/LICENSE) file for details.
