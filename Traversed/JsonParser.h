#pragma once

#include "External/Json/parson.h"
#include "External/MathGeo/include/Math/float3.h"
#include "External/MathGeo/include/Math/float4.h"
#include "External/MathGeo/include/Math/Quat.h"

class JsonParser
{
public:
	JsonParser();
	JsonParser(const char* string);
	JsonParser(JSON_Value* value);
	~JsonParser();

	size_t Save(char** buf);
	size_t SaveFile(const char* name);

	JSON_Object* SetNewJsonNode(JSON_Object* parent, const char* nodeName) const;
	JSON_Status SetNewJsonString(JSON_Object* node, const char* name, const char* string) const;
	JSON_Status SetNewJsonNumber(JSON_Object* node, const char* name, double number) const;
	JSON_Status SetNewJson3Number(JsonParser& node, const char* name, float3 number) const;
	JSON_Status SetNewJson4Number(JsonParser& node, const char* name, Quat number) const;
	JSON_Status SetNewJsonBool(JSON_Object* node, const char* name, bool boolean) const;
	JSON_Array* SetNewJsonArray(JSON_Value* parent, const char* name) const;
	JSON_Status SetValueToArray(JSON_Array* jsonArray, JSON_Value* value);
	JsonParser SetChild(JSON_Value* parent, const char* name);

	JSON_Object* GetJsonObject(JSON_Object* parentObject, const char* node) const;
	JSON_Array* GetJsonArray(JSON_Object* parentObject, const char* node) const;
	size_t GetJsonArrayCount(JSON_Array* array) const;
	JSON_Value* GetRootValue() const;
	const char* GetJsonString(const char* name) const;
	double GetJsonNumber(const char* name) const;
	bool GetJsonBool(const char* name) const;
	JsonParser GetChild(JSON_Value* parent, const char* name);

	JsonParser GetJsonArrayValue(JSON_Array* array, int index) const;
	float3 GetJson3Number(JsonParser& node, const char* name);
	float4 GetJson4Number(JsonParser& node, const char* name);
	//GetValor("Width")

	size_t ParseFile(const char* fileName);
	JSON_Object* ValueToObject(JSON_Value* value) const;
	JSON_Status SerializeFile(JSON_Value* value, const char* fileName) const;

	JSON_Value* InitObject();
private:

	JSON_Value* rootObject;

};
