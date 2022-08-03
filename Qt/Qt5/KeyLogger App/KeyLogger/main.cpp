#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QTime>
#include <QChar>
#include <Windows.h>
#include <iostream>
//#pragma comment(lib, "user32.lib")
//#pragma có nhiệm vụ chỉ dẫn thực hiện 1 thao tác cụ thể nào đó. Nó k có 1 chuẩn mực nào mà tùy vào trình dịch
//Ở đây nó có ý nghĩa là dùng thư viện gì nhưng ở phiên bản Qt này nó k cần thiết nx

HHOOK hHook = NULL;//tạo biến hook cho vc setup. Handle of the hook

using namespace std;

void UpdateKeyState(BYTE *keystate, int keycode)
{
    keystate[keycode] = GetKeyState(keycode);
    //hàm GetKeyState là tương tự nhưng dùng với 1 key cụ thể
    //GetAsyncKeyState tương tự nhưng nó sẽ truy cập bất kể thông báo từ phím đó đã truy xuất từ hàng đợi hay chưa
}

LRESULT CALLBACK MyLowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
//LRESULT là kết quả của message nó xử lý, cx chỉ là long, LPARAM cx chỉ là long int.WPARAM là UNIT_PTR là unsigned int
//cái tiền tố L hay W đằng trước chỉ là ý nghĩa lịch sử thôi.
{
    //WPARAM is WM_KEYDOWN, WM_KEYUP, WM_SYSKEYDOWN, or WM_SYSKEYUP
    //LPARAM is the key information

    //Nó tính 2 lần khi ấn vì 2 TT pressed và nhả
    //Get the key information
    if(wParam == WM_KEYUP)
    return CallNextHookEx(hHook, nCode, wParam, lParam);
    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
    //KBDLLHOOKSTRUCT là 1 struct chứa thông tin về low-level keyboard input event

    wchar_t buffer[5];

    //get the keyboard state
    BYTE keyboard_state[256];//là unsigned char
    GetKeyboardState(keyboard_state);//nhận kiểu PBYTE là pointer to byte, trả ra bool, false cho 0
    //hàm này copy trạng thái hiện tại của 256 virtual key vào bộ đệm. Sau khi gọi, từng phần tử của keyboard_state sẽ lưu TT
    //nếu highorder bit is 1 thì key down, ngc lại là key up.
    //Thực ra mỗi máy tính có thứ gọi là native word là 16 bit word size. Nhưng ở các máy tính hiện đại thì CPU là 32 bit nên
    //ta thấy thường là double word(ký hiệu thg là DWORD) thực ra là 2 words 16 bit
    //VD ta có 1 32-bit DWORD 01101001 00101000 00001101 01011100, thì highoder bit là cái bên trái ngoài cùng là 0 tương tự
    //vơi lower. Còn highorder word hay byte là 01101001 00101000 chia đôi lấy hai cái bên trái, tương tự vs lower
    //Tức là ở đây, nếu bit bên trái ngoài cùng là 1 thì là keydown, còn các bit khác có vai trò khác ta k xét
    //tức lúc này cái biến keyboard state có 256 phần tử, mỗi phần tử là kích thước của BYTE là 8bit, và cứ cái nào đang ấn thì
    //bit đầu phần tử sẽ là 1
    UpdateKeyState(keyboard_state, VK_SHIFT);
    UpdateKeyState(keyboard_state, VK_CAPITAL);
    UpdateKeyState(keyboard_state, VK_CONTROL);
    UpdateKeyState(keyboard_state, VK_MENU);

    //Get keyboard layout
    HKL keyboard_layout = GetKeyboardLayout(0);
    //lấy ra cái identifier đầu vào, truyền vào identifier of thread to querry or 0 nếu là current thread
    // trả ra HKL là identifier đầu vào, là identifier cái phím bấm

    //Get the name
    char lpszName[0x100] = {0};

    DWORD dwMsg = 1;
    dwMsg += cKey.scanCode << 16;
    dwMsg += cKey.flags << 24;// chưa đủ trình để hiểu
    //phép dịch bit

    int i = GetKeyNameText(dwMsg, (LPTSTR)lpszName,255);
    //lấy tên of key lưu vào đối số 2, 3 là maximum length of key name kể cả ký tự null, nên bằng kích thước đố số 2.
    //GetKeyNameText dùng cho basic_String char* version, còn GetKeyNameTextA dùng cho string version

    //Try to convert the key info
    int result = ToUnicodeEx(cKey.vkCode, cKey.scanCode, keyboard_state, buffer,4,0, keyboard_layout);
    buffer[4] = L'\0';//cùng lắm là 2 ký tự \n,\r là cùng nên 4 là nh r
    //vk là virtual key. K có '\0' ở cuối thì k là 1 string nên cần chuyển nó đúng là string
    //chuyển keycode và keyboard state sang unicode character
    //UINT virtual keycode cần chuyển,UINT,BYTE* con trỏ trỏ vào keyboard state,lưu unicode vào 4, với kích thước 5,
    //6 lưu behavior of func kệ nó, 7 là layout

    //Print the output
    qDebug() << "key: " << cKey.vkCode << " " << QString::fromUtf16((ushort*)buffer) << " "
                        << QString::fromUtf16((ushort*)lpszName);
    //buffer sẽ in ra thực tế, còn lpszName in tên
    //buffer là ký tự của ta dưới dạng unicode (hay ASCII cx v), là cái bth ta viết ra ấy, còn lpszName là char* lưu text r

    return CallNextHookEx(hHook, nCode, wParam, lParam);
    //truyền hook vào cái hook procedure trong cái hook chain hiện tại

    //vk lưu số,getNameText lưu chữ tên phím, toUnicodeEx sẽ lưu ký tự sẽ hiện ra biểu diễn ở unicode(vd enter là \n)
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //đây là 1 global hook, bắt ở bất kỳ đâu

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelKeyBoardProc, NULL, 0);
    if(hHook == NULL)
    {
        qDebug() << "Hook failed: " << GetLastError();
    }
    // Nếu thành công thì biến HHOOK sẽ chờ bắt sự kiện, nếu bắt đc thì sẽ thực hiện hookproc

    return a.exec();
}
//cấu trúc đơn giản nhất của 1 Ct hooking: tạo biến hook global-> dùng SetWindowHookEx-> tạo hàm CALLBACK-> xử lý bên trong
//CALLBACK-> return CallNextHookEx
