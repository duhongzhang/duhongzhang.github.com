class testString {
    std::string str;
public:
    testString(std::string str) : str(str) {}
    bool isEmpty() { return str.empty(); }
    int str2int() { return std::stoi(str); }
};