#include <windows.h>

#include <gl\gl.h>
#include <gl\\glu.h>


#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

/*
Главная библиотека для создания окна,
включает HINSTANCE,HWND,HDC и т.д.
*/

HINSTANCE hinstance_application;// дескриптор приложения 
HWND hwnd_window;// дескриптор окна
HDC hdc_main;//Дескриптор контекста устройства

const char* pc_WindowClassName = "WindowClass";
const char* pc_wndTitle = "Windows приложение";


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
/*
APIENTRY определяет как фунция будет обращаться с аргументами в стеке
куда помещаются аргументы
*/

BOOL InitializeApp(void);
void UninitializeApp(void);
void UnregisterWndClasses(void);

BOOL CreateWindows(void);
BOOL RegisterClassaOkna(void);

LRESULT CALLBACK MainWindowProc(HWND, UINT, WPARAM, LPARAM);

BOOL MainOnCreate(HWND);
BOOL MainOnDestroy(HWND);
BOOL MainOnPaint(HWND);
BOOL MainOnSize(HWND, int, int);
BOOL MainOnLButtonDown(HWND , int , int );
BOOL MainOnMouseMove(HWND , int , int , UINT );


int WINAPI WinMain(HINSTANCE hi_crr, HINSTANCE, LPSTR, int)
{
	MSG msg;
	/*
	Содержит информармацию о передаваемых сообщениях
	*/

	InitializeApp();
	BOOL return_;
	while (return_ = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (return_ == -1)
		{
			MessageBox(hwnd_window, "return_ = -1", "Ошибка", MB_ICONSTOP);
			return 0;
		}
		else
		{
			TranslateMessage(&msg);
			/*
			Из WM_KEYDOWN/WM_KEYUP формирует сообщения
			WM_CHAR/WM_SYSCHAR
			*/
			DispatchMessage(&msg);
			/*
			Отправляет сообщения в оконную процедуру
			*/
		}
	}
	UninitializeApp();
	/*
	Извлекает сообщение из очереди сообщений вызывающего потока
	и помещает его в заданную структуру, регуляирует поступление
	отправленных сообщений пока оно доступно для извлечения
	GetMessage(указатель на MSG,которая принимает информацию из очереди сообщенийб
	Дескриптор окна, чьи сообщения должны быть извлечены
	NULL => извлекает сообщения любого окна,
	с какого значения начнется
	0 => возвращает все доступные сообщения ,
	на каком значении остановиться,
	0 => возвращает все доступные сообщения)
	if извлекает WM_QUIT, то возвращает 0, else !0
	*/
	return msg.wParam;
}
/*
Основная функция
WinMain(дескриптор процесса(число идентифицирующее программу),
предыдущий дескриптор процесса устарел и =0,
указатель на параметры переданные в программу из cmd,
показывает каким должно быть выведено окно на экран)
*/
BOOL InitializeApp()
{
	if (!RegisterClassaOkna())
	{
		MessageBox(NULL, "Ошибка регистрации классов окон", pc_wndTitle, MB_OK);
		//MessageBox(дескриптор окна владельца,символьная строка,заголовок окна,режим работы окна)
	}
	CreateWindows();
	ShowWindow(hwnd_window, SW_SHOW);
	//ShowWindow(дескриптор окна, режим показа окна)
	UpdateWindow(hwnd_window);
	//Обновляет рабочую область заданного окна
	return TRUE;
}
void UninitializeApp()
{
	UnregisterWndClasses();

}
void UnregisterWndClasses()
{
	UnregisterClass(pc_WindowClassName, hinstance_application);
	/*
	Отменяет регистрацию класса окна, освобождая память
	*/
}
BOOL CreateWindows()
{

	hwnd_window = CreateWindow(pc_WindowClassName,// Имя класса
		pc_wndTitle,// Имя окна 
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX |//Стили окна:1.Создает перекрывающее окно 2.Наличие меню окна 3.Кнопка свертывания 
		WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN,//4.Кнопка развертывания 5. Рамка с изменением размеров 6.Исключает область дочерних окон при прорисовки в родительском окне
		0,// Положение окна по оси X по умолчанию
		0,// Положение окна по оси Y по умолчанию 
		800,// Ширина окна 
		600,// Высота окна 
		NULL,// Дескриптор родительского окна(у нас его нет)
		NULL,// Дескриптор меню 
		hinstance_application,// Дескриптор экземпляра приложения 
		0// Указатель на данные передаваемые из пользовательской функции WndProc
	);
	hdc_main = GetDC(hwnd_window);
	/*
	Извлекает дескриптор дисплейного контекста устройства для рабочей области
	Можно использовать дескриптор в последующих функциях для рисования в контексте устройства
	*/

	return TRUE;
}
BOOL RegisterClassaOkna(void)
{
	WNDCLASSEX wce_main;
	//Создает структуру содержащую атрибуты класса окна с приставкой wce_main
	memset(&wce_main, 0, sizeof(WNDCLASSEX));
	//заполнить первое колличество символов(равное WNDCLASSEX) нулями
	wce_main.cbSize = sizeof(WNDCLASSEX);
	//Устанавливает размер этой структуры в байтах
	wce_main.hInstance = hinstance_application;
	//Дескриптор экземпляра модуля который создал класс
	wce_main.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
	//стиль класса
	wce_main.lpfnWndProc = (WNDPROC)MainWindowProc;
	//Адесс оконной функции
	wce_main.hCursor = LoadCursor(NULL, IDC_ARROW);
	//Курсор мыши для Окна
	wce_main.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//Кисть для окон
	wce_main.lpszClassName = pc_WindowClassName;
	//Имя класса окна 
	return RegisterClassEx(&wce_main);
	//возвращает адрес структуры с данными класса

}
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
			return MainOnCreate(hwnd);
			//Сообщения от мыши 
	case WM_SIZE:
		return MainOnSize(hwnd, LOWORD(lParam), HIWORD(lParam));
	case WM_LBUTTONDOWN:
		return MainOnLButtonDown(hwnd, LOWORD(lParam), HIWORD(lParam));
	case WM_RBUTTONDOWN:

	case WM_MOUSEWHEEL:

		//Прокрутка колесика
	case WM_KEYDOWN:

		// клавиша отпущена (первичное сообщение)
	case WM_MOUSEMOVE:
		return MainOnMouseMove(hwnd, LOWORD(lParam), HIWORD(lParam), wParam);
		//Перемещение мыши в клиентской области 
	case WM_SYSCHAR:

		//ALT,SHIFT...
	case WM_PAINT:
		return MainOnPaint(hwnd);
		//Окрас части окна 
	case WM_DESTROY:
		return MainOnDestroy(hwnd);
		//Отправляется это сообщение при разрушении окна
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
		//Обрабатывает любые сообщения 

	}
	return 0L;
}
/*
Главная оконная процедура
LRESULT => целочисленное значение, которое возвращается в Windows
CALLBACK => Для передачи ссылки функции в другую функцию
*/

BOOL MainOnDestroy(HWND hwnd)
{
	ReleaseDC(hwnd, hdc_main);
	PostQuitMessage(0);
	return TRUE;
}

