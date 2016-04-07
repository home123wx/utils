#include <iostream>
#include <string>
using namespace std;

#include "json/json.h"
using namespace Json;

/*
int main()
{
        string test = "{\"test\":5}";
        
        Reader reader;
        Value value;

        if (reader.parse(test, value)) {
                int i = 0;
                if (!value["test"].isNull()) {
                        i = value["test"].asInt();
                        cout << i << endl;
                }
        }
        
        Value root;
        Value arrayObj;
        Value item;
        for (int i=0; i<10; i++) {
                item["key"] = i;
                arrayObj.append(item);
        }

        root["key1"] = "value1";
        root["key2"] = "value2";
        root["array"] = arrayObj;
        root.toStyledString();

        string out = root.toStyledString();
        cout << out << endl;

        return 0;
}
*/
