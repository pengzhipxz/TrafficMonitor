//ini��д��
//ʹ��ʱ��ini�ļ�·��ͨ�����캯����������
//����ini�ļ�д������ʱ����Ҫ��������Save()�����Խ����ı��浽�ļ�
//Ĭ����UTF8_BOM���뱣�棬���Ҫ��ANSI���棬�����SetSaveAsUTF8(false);
#pragma once
#include "CommonData.h"
#include "Common.h"

class CIniHelper
{
public:
	CIniHelper(const wstring& file_path);
	~CIniHelper();

	void SetSaveAsUTF8(bool utf8);

	void WriteString(const wchar_t* AppName, const wchar_t* KeyName, const wstring& str);
	wstring GetString(const wchar_t* AppName, const wchar_t* KeyName, const wchar_t* default_str) const;
	void WriteInt(const wchar_t * AppName, const wchar_t * KeyName, int value);
	int GetInt(const wchar_t * AppName, const wchar_t * KeyName, int default_value) const;
	void WriteBool(const wchar_t * AppName, const wchar_t * KeyName, bool value);
	bool GetBool(const wchar_t * AppName, const wchar_t * KeyName, bool default_value) const;
	void WriteIntArray(const wchar_t * AppName, const wchar_t * KeyName, const int* values, int size);		//д��һ��int���飬Ԫ�ظ���Ϊsize
	void GetIntArray(const wchar_t * AppName, const wchar_t * KeyName, int* values, int size, int default_value = 0) const;		//��ȡһ��int���飬���浽values��Ԫ�ظ���Ϊsize
	void WriteBoolArray(const wchar_t * AppName, const wchar_t * KeyName, const bool* values, int size);
	void GetBoolArray(const wchar_t * AppName, const wchar_t * KeyName, bool* values, int size, bool default_value = false) const;

	void SaveFontData(const wchar_t * AppName, const FontInfo& font);
	void LoadFontData(const wchar_t * AppName, FontInfo& font, const FontInfo& default_font) const;

	bool Save();		//��ini�ļ����浽�ļ����ɹ�����true

protected:
	wstring m_file_path;
	wstring m_ini_str;
	bool m_save_as_utf8{ true };		//�Ƿ��Լ�UTF8���뱣��

	void _WriteString(const wchar_t* AppName, const wchar_t* KeyName, const wstring& str);
	wstring _GetString(const wchar_t* AppName, const wchar_t* KeyName, const wchar_t* default_str) const;
};

