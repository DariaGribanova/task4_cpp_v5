
// MFCApplication1Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "afx.h"
#include <string>
#include <atlstr.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
enum class LogLevel
{
	Info,
	Warning,
	Error
};
void log(LogLevel level, const std::string& message)
{
	std::ofstream logFile("log.txt", std::ios_base::app);
	if (logFile.is_open())
	{
		const char* levelStr = "";
		switch (level)
		{
		case LogLevel::Info:
			levelStr = "INFO";
			break;
		case LogLevel::Warning:
			levelStr = "WARNING";
			break;
		case LogLevel::Error:
			levelStr = "ERROR";
			break;
		}

		time_t now = time(NULL);
		struct tm local_time;
		localtime_s(&local_time, &now);
		char time_str[26];
		asctime_s(time_str, sizeof(time_str), &local_time);
		std::string str_time_str(time_str);
		str_time_str.erase(std::remove(str_time_str.begin(), str_time_str.end(), '\n'), str_time_str.end());
		logFile << "[" + str_time_str + "] " + levelStr + ": " + message;
		logFile << "\n";


	}
}

// Диалоговое окно CMFCApplication1Dlg



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, _List);
	DDX_Control(pDX, IDC_LIST2, _File);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFCApplication1Dlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplication1Dlg

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CDialog::SetWindowTextW(L"Словарь, пополняемый словами из файлов");

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

map<CString, int> words;


bool cmp(const std::pair<CString, int>& a, const std::pair<CString, int>& b) {
	return a.second > b.second;
}
vector<std::pair<CString, int>> sort_map_by_value() {
	std::vector<std::pair<CString, int>> vec(words.begin(), words.end());
	std::sort(vec.begin(), vec.end(), cmp);
	std::map<CString, int> sorted_words;
	for (auto const& pair : vec) {
		sorted_words[pair.first] = pair.second;
	}
	return vec;
}

void addWord(CString word) {
	if (word.IsEmpty()) {
		return;
	}
	CString lowerCaseWord = word.MakeLower();
	if (words.find(lowerCaseWord) == words.end()) {
		words[lowerCaseWord] = 1;
	}
	else {
		words[lowerCaseWord]++;
	}
}

void addWord2(CString word, int count = 1) {
	if (words.find(word) != words.end()) {
		words[word] += count;
	}
	else {
		words[word] = count;
	}
}


// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	CString filter = _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("txt"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter, this);
	if (dlg.DoModal() != IDOK)
		return;
	CString filename = dlg.GetPathName();
	std::ifstream file(filename);
	string line;
	words.clear();
	while (getline(file, line)) {
		try {
			istringstream iss(line);
			string word;
			int count;
			if (iss >> word >> count) {
				CString str1(word.c_str());
				addWord2(str1, count);
			}
			else {
				log(LogLevel::Warning, "Неправильный формат");
				//throw std::runtime_error("Invalid format");
				break;
			}
		}
		catch (const std::exception& e) {
			// Обрабатываем исключение
			log(LogLevel::Error, "Не удалось открыть файл");
			return;
		}
		_List.ResetContent();
		for (auto pair : words) {
			_List.AddString(pair.first + CString(" ") + to_string(pair.second).c_str() + CString("\r\n"));
		}
	}
	log(LogLevel::Info, "Открыт словарь из файла");
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// Открыть файл
	CString filter = _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("txt"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter, this);
	if (dlg.DoModal() != IDOK)
		return;
	CString filename = dlg.GetPathName();
	std::ifstream file(filename);
	std::string line;
	_File.ResetContent();
	while (std::getline(file, line))
	{
		_File.AddString(CString(line.c_str()));
	}
	log(LogLevel::Info, "Открыт файл");

}


void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// Добавить в словарь
		CString all_text = _T("");
		for (int i = 0; i < _File.GetCount(); i++) {
			CString item_text;
			_File.GetText(i, item_text);
			all_text += item_text + _T(" ");
		}
		std::vector<CString> words1;
		int start = 0;
		for (int i = 0; i < all_text.GetLength(); i++) {
			if (all_text[i] == ' ') {
				words1.push_back(all_text.Mid(start, i - start));
				start = i + 1;
			}
		}
		words1.push_back(all_text.Mid(start));
		for (const auto& word : words1) {
			addWord(word);
		}
		_List.ResetContent();
		for (auto pair : words) {
			_List.AddString(pair.first + CString(" ") + to_string(pair.second).c_str() + CString("\r\n"));
		}
		log(LogLevel::Info, "Файл добавлен в словарь");
}



void CMFCApplication1Dlg::OnLbnSelchangeList1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// Сортировка по встречаемости
	vector<std::pair<CString, int>> vec = sort_map_by_value();
	_List.ResetContent();
	for (auto const& pair : vec) {
		_List.AddString(pair.first + CString(" ") + to_string(pair.second).c_str() + CString("\r\n"));
	}
	log(LogLevel::Info, "Сортировка словаря по встречаемости");
}
void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// Сортировка по алфавиту
	_List.ResetContent();
	for (auto pair : words) {
		_List.AddString(pair.first + CString(" ") + to_string(pair.second).c_str() + CString("\r\n"));
	}
	log(LogLevel::Info, "Сортировка словаря по алфавиту");
}

void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// Сохранить словарь в файл
	CString filename;
	CFileDialog dlg(FALSE);
	if (dlg.DoModal() == IDOK) {
		filename = dlg.GetPathName();
		ofstream file(filename);
		if (file.is_open()) {
			for (auto pair : words) {
				file << CT2A(pair.first.GetString()) << " " << pair.second << endl;
			}
			file.close();
		}
	}
	log(LogLevel::Info, "Словарь сохранён в файл");
}
