#include <iostream>
#include <math.h> // Để dùng sqrt() cho hàm SNT
#include <queue>  // Để dùng cho hàm duyệt theo chiều rộng (nếu cần)

using namespace std;

// === 1. ĐỊNH NGHĨA CẤU TRÚC ===
// Đây là "viên gạch" xây nên cái cây
struct Node {
    int data;       // Dữ liệu của nút, bạn gọi là "data"
    Node *pleft;    // Con trỏ đến cây con TRÁI
    Node *pright;   // Con trỏ đến cây con PHẢI
};

// Dùng typedef để tạo bí danh "TREE" cho "Node *"
// Giờ đây, "TREE" có nghĩa là "một con trỏ trỏ đến Node",
// ta thường dùng nó để chỉ "nút gốc" (root) của một cây.
typedef Node *TREE;

// === 2. NHÓM KHỞI TẠO & THÊM NODE ===
// "Khởi tạo" một cái cây (chỉ là cho nó rỗng)
void Init(TREE &t) {
    t = NULL; // NULL có nghĩa là cây rỗng, không có nút nào
}

// "Tạo Nút Mới" - Giống như bạn tạo một viên gạch mới
// Hàm này sẽ tạo 1 Node mới với dữ liệu x
Node* CreateNewNode(int x) {
    Node *p = new Node; // Xin cấp phát một Node mới
    if (p == NULL) {
        cout << "Loi: Khong du bo nho!" << endl;
        return NULL;
    }
    p->data = x;       // Gán dữ liệu
    p->pleft = NULL;   // Mới tạo ra nên chưa có con trái
    p->pright = NULL;  // và chưa có con phải
    return p;          // Trả về viên gạch mới
}

// "Thêm Node Vào Cây" (Giả định là Cây Nhị Phân Tìm Kiếm - BST)
// Kỹ thuật gợi nhớ: "Lớn qua Phải, Nhỏ qua Trái"
void ThemNodeVaoCay(TREE &t, int x) {
    // 1. Nếu cây đang rỗng (t == NULL)
    if (t == NULL) {
        t = CreateNewNode(x); // Thì nút mới chính là gốc
    }
    // 2. Nếu cây không rỗng
    else {
        // Nếu x NHỎ HƠN data của nút hiện tại
        if (x < t->data) {
            ThemNodeVaoCay(t->pleft, x); // "Nhỏ qua Trái": Đệ quy thêm vào cây con trái
        }
        // Nếu x LỚN HƠN data của nút hiện tại
        else if (x > t->data) {
            ThemNodeVaoCay(t->pright, x); // "Lớn qua Phải": Đệ quy thêm vào cây con phải
        }
        // Trường hợp x == t->data: Không làm gì (BST không lưu khóa trùng)
    }
}

// "Đọc File" và tạo cây
// (Giả sử file "input.txt" chỉ chứa các số nguyên)
void Doc_file(char *tenfile, TREE &t) {
    FILE *f = fopen(tenfile, "r");
    if (f == NULL) {
        cout << "Loi: Khong mo duoc file " << tenfile << endl;
        return;
    }

    int x;
    // Đọc từng số từ file cho đến khi hết
    while (fscanf(f, "%d", &x) != EOF) {
        ThemNodeVaoCay(t, x); // Thêm số vừa đọc vào cây
    }

    fclose(f);
    cout << "Da doc file va tao cay thanh cong!" << endl;
}


// === 3. NHÓM DUYỆT CÂY (TRAVERSAL) ===
// Kỹ thuật gợi nhớ: "N" là Nút (Node), "L" là Trái (Left), "R" là Phải (Right)
// Vị trí của "N" quyết định tên của phép duyệt!

// 1. NLR (PreOrder) - "N" ở ĐẦU
// Kỹ thuật gợi nhớ: "Thăm Nút (N) ngay, rồi đi Lòng vòng (L), cuối cùng Rẽ phải (R)"
void Xuat_NLR(TREE t) {
    if (t != NULL) {
        cout << t->data << " "; // Thăm "N" (Nút)
        Xuat_NLR(t->pleft);   // Đi "L" (Trái)
        Xuat_NLR(t->pright);  // Đi "R" (Phải)
    }
}

// 2. LNR (InOrder) - "N" ở GIỮA
// Kỹ thuật gợi nhớ: "Chờ Lâu (L) mới thăm Nó (N), rồi đi Riêng (R)"
// ** Đặc biệt: Duyệt LNR trên cây BST sẽ cho ra dãy số TĂNG DẦN **
void Xuat_LNR(TREE t) {
    if (t != NULL) {
        Xuat_LNR(t->pleft);   // Đi "L" (Trái)
        cout << t->data << " "; // Thăm "N" (Nút)
        Xuat_LNR(t->pright);  // Đi "R" (Phải)
    }
}

// 3. LRN (PostOrder) - "N" ở CUỐI
// Kỹ thuật gợi nhớ: "Đi Lòng vòng (L), Ra ngoài (R), mới thăm Nó (N) cuối cùng"
void Xuat_LRN(TREE t) {
    if (t != NULL) {
        Xuat_LRN(t->pleft);   // Đi "L" (Trái)
        Xuat_LRN(t->pright);  // Đi "R" (Phải)
        cout << t->data << " "; // Thăm "N" (Nút)
    }
}

// 4. Các hàm duyệt khác trong ảnh của bạn (ví dụ: NRL)
// Chỉ cần thay đổi thứ tự là xong!
void Xuat_NRL(TREE t) {
     if (t != NULL) {
        cout << t->data << " "; // Thăm "N" (Nút)
        Xuat_NRL(t->pright);  // Đi "R" (Phải) - thay đổi ở đây
        Xuat_NRL(t->pleft);   // Đi "L" (Trái) - thay đổi ở đây
    }
}

// === 4. NHÓM TÌM KIẾM & TÍNH TOÁN ===

// "Tìm Kiếm" một giá trị x trong BST
Node* TimKiem(TREE t, int x) {
    if (t == NULL) {
        return NULL; // Cây rỗng, không tìm thấy
    }

    if (x < t->data) {
        return TimKiem(t->pleft, x); // "Nhỏ qua Trái"
    } else if (x > t->data) {
        return TimKiem(t->pright, x); // "Lớn qua Phải"
    } else { // x == t->data
        return t; // Tìm thấy! Trả về chính nút đó
    }
}

// "Tìm Max" trong BST: Đơn giản là đi hết sang PHẢI
// Kỹ thuật gợi nhớ: "Max thì Mê Phải"
int TimMax(TREE t) {
    if (t == NULL) return -1; // Trường hợp cây rỗng
    
    // Nếu nút bên phải là NULL, thì nút hiện tại là max
    if (t->pright == NULL) {
        return t->data;
    }
    // Nếu không, tiếp tục "Mê Phải"
    return TimMax(t->pright);
}

// "Tìm Min" trong BST: Đơn giản là đi hết sang TRÁI
// Kỹ thuật gợi nhớ: "Min thì Mê Trái"
int TimMin(TREE t) {
    if (t == NULL) return -1;

    if (t->pleft == NULL) {
        return t->data;
    }
    return TimMin(t->pleft);
}

// "Tính Chiều Cao" của cây
// Kỹ thuật gợi nhớ: "Chiều cao = 1 (tầng hầm) + Max(chiều cao của 2 đứa con)"
int ChieuCao(TREE t) {
    if (t == NULL) {
        return 0; // Cây rỗng (hoặc lá) thì không cao
    }
    
    int h_left = ChieuCao(t->pleft);   // Chiều cao con trái
    int h_right = ChieuCao(t->pright); // Chiều cao con phải
    
    // Lấy đứa con cao hơn, rồi cộng thêm 1 (là chính nó)
    return 1 + max(h_left, h_right);
}

// "Tổng" tất cả các Node
int Sum(TREE t) {
    if (t == NULL) {
        return 0; // Cây rỗng thì tổng = 0
    }
    // Tổng = Data của nó + Tổng con trái + Tổng con phải
    return t->data + Sum(t->pleft) + Sum(t->pright);
}


// === 5. NHÓM ĐẾM & LIỆT KÊ ===

// "Đếm Node" (Tổng số nút)
int DemNode(TREE t) {
    if (t == NULL) {
        return 0; // Rỗng thì có 0 nút
    }
    // Đếm = 1 (là nó) + Đếm con trái + Đếm con phải
    return 1 + DemNode(t->pleft) + DemNode(t->pright);
}

// "Đếm Node Lá" (Node 0 con)
int DemNodeLa(TREE t) {
    if (t == NULL) {
        return 0;
    }
    // Nếu nó không có con trái VÀ không có con phải -> nó là LÁ
    if (t->pleft == NULL && t->pright == NULL) {
        return 1; // Đếm là 1
    }
    // Nếu không phải lá, thì đi tìm lá ở 2 con
    return DemNodeLa(t->pleft) + DemNodeLa(t->pright);
}

// "Xuất Node 1 con"
void XuatNode1Con(TREE t) {
    if (t == NULL) return;
    
    // Điều kiện 1 con: (Trái CÓ và Phải KHÔNG) HOẶC (Trái KHÔNG và Phải CÓ)
    if ((t->pleft != NULL && t->pright == NULL) || (t->pleft == NULL && t->pright != NULL)) {
        cout << t->data << " ";
    }
    
    // Tiếp tục tìm ở 2 con
    XuatNode1Con(t->pleft);
    XuatNode1Con(t->pright);
}

// "Xuất Node 2 con"
void XuatNode2Con(TREE t) {
    if (t == NULL) return;
    
    // Điều kiện 2 con: Trái CÓ VÀ Phải CÓ
    if (t->pleft != NULL && t->pright != NULL) {
        cout << t->data << " ";
    }
    
    XuatNode2Con(t->pleft);
    XuatNode2Con(t->pright);
}


// === 6. NHÓM HÀM CHUYÊN BIỆT (Số Nguyên Tố) ===

// "Kiểm Tra SNT" (Prime Number)
bool KiemTraSNT(int x) {
    if (x < 2) return false; // SNT phải >= 2
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false; // Chia hết -> không phải SNT
        }
    }
    return true; // Không chia hết cho ai -> là SNT
}

// "Đếm Số Lượng SNT" trong cây
// Dùng biến tham chiếu `&dem` để đếm
void SoLuongSNT(TREE t, int &dem) {
    if (t != NULL) {
        // Xử lý nút hiện tại (N)
        if (KiemTraSNT(t->data)) {
            dem++;
        }
        // Đệ quy 2 con (L, R)
        SoLuongSNT(t->pleft, dem);
        SoLuongSNT(t->pright, dem);
    }
}

// "Tìm SNT Nhỏ Nhất"
// (Dùng kỹ thuật "cận" - `&min_snt` ban đầu truyền vào giá trị rất lớn)
void SNTNhoNhat(TREE t, int &min_snt) {
    if (t != NULL) {
        if (KiemTraSNT(t->data) && t->data < min_snt) {
            min_snt = t->data; // Cập nhật min
        }
        SNTNhoNhat(t->pleft, min_snt);
        SNTNhoNhat(t->pright, min_snt);
    }
}


// === 7. NHÓM XÓA NODE (KHÓ NHẤT) ===
// Kỹ thuật gợi nhớ: "Xóa Node" có 3 trường hợp:
// 1. "Lá rụng": Node cần xóa là lá (0 con) -> Xóa luôn.
// 2. "Gãy cành, nối thân": Node cần xóa có 1 con -> Nối con nó vào ông nội nó.
// 3. "Tìm người thế mạng": Node cần xóa có 2 con -> Khó nhất!
//    -> Tìm 1 người "thế mạng" (substitute) cho nó.
//    -> Người thế mạng là: "Con Trái Nhất của Cây Con Phải" (hoặc ngược lại).

// Hàm helper: "Tìm người thế mạng" (Tìm con TRÁI NHẤT của cây con PHẢI)
// Cũng chính là tìm Node Min bên cây con Phải
void TimNodeTheMang(TREE &t_the_mang, TREE &node_can_xoa) {
    // Nếu `t_the_mang` vẫn còn con trái, ta đi tiếp
    if (t_the_mang->pleft != NULL) {
        TimNodeTheMang(t_the_mang->pleft, node_can_xoa);
    }
    // Đã đi hết sang trái -> `t_the_mang` chính là người thế mạng
    else {
        // 1. "Đánh cắp" data của người thế mạng:
        //    Gán data của người thế mạng cho data của nút cần xóa
        node_can_xoa->data = t_the_mang->data;
        
        // 2. "Thủ tiêu" người thế mạng:
        //    Vì `t_the_mang` là con trái nhất, nó chắc chắn không có con trái.
        //    Nó có thể có con phải (trường hợp 1 con).
        //    Ta "nối" con phải của nó vào cha nó.
        Node *temp = t_the_mang; // Giữ lại người thế mạng để free
        node_can_xoa = t_the_mang->pright; // Nối cành (con phải)
        
        delete temp; // Xóa người thế mạng
    }
}


// "Xóa Node" có giá trị x
void XoaNode(TREE &t, int x) {
    if (t == NULL) {
        return; // Cây rỗng, không có gì để xóa
    }

    // 1. ĐI TÌM NODE CẦN XÓA (giống hàm TimKiem)
    if (x < t->data) {
        XoaNode(t->pleft, x); // Đi tìm bên trái
    } else if (x > t->data) {
        XoaNode(t->pright, x); // Đi tìm bên phải
    }
    // 2. ĐÃ TÌM THẤY (x == t->data). `t` là nút cần xóa.
    else {
        Node *node_bi_xoa = t; // Giữ lại để free

        // Case 1: "Lá rụng" (0 con)
        if (t->pleft == NULL && t->pright == NULL) {
            t = NULL; // Cha trỏ vào NULL
            delete node_bi_xoa;
        }
        // Case 2: "Gãy cành" (1 con)
        // 2a. Chỉ có con PHẢI
        else if (t->pleft == NULL) {
            t = t->pright; // Cha trỏ vào con phải
            delete node_bi_xoa;
        }
        // 2b. Chỉ có con TRÁI
        else if (t->pright == NULL) {
            t = t->pleft; // Cha trỏ vào con trái
            delete node_bi_xoa;
        }
        // Case 3: "Tìm người thế mạng" (2 con)
        else {
            // Tìm người thế mạng ở "Cây con Phải"
            // (Chính là con TRÁI NHẤT của cây con PHẢI)
            TimNodeTheMang(t->pright, t);
        }
    }
}


// === 8. HÀM MAIN (ĐỂ CHẠY THỬ) ===
int main() {
    TREE t;
    Init(t); // Khởi tạo cây rỗng

    // Thêm vài node vào cây
    ThemNodeVaoCay(t, 50);
    ThemNodeVaoCay(t, 30);
    ThemNodeVaoCay(t, 70);
    ThemNodeVaoCay(t, 20);
    ThemNodeVaoCay(t, 40);
    ThemNodeVaoCay(t, 60);
    ThemNodeVaoCay(t, 80);
    ThemNodeVaoCay(t, 35); // Thêm node để test SNT
    ThemNodeVaoCay(t, 11); // Thêm node để test SNT

    /*
         Cây sẽ có dạng:
                50
              /    \
             30     70
            /  \   /  \
           20  40 60  80
          /   /
         11  35 
    */

    cout << "--- Cac phep duyet cay ---" << endl;
    cout << "Duyet NLR (PreOrder):  "; Xuat_NLR(t); cout << endl;
    cout << "Duyet LNR (InOrder):   "; Xuat_LNR(t); cout << endl; // Sẽ ra dãy 20 30 35 40 50 60 70 80
    cout << "Duyet LRN (PostOrder): "; Xuat_LRN(t); cout << endl;
    cout << "Duyet NRL (Tu an_h): "; Xuat_NRL(t); cout << endl;

    cout << "\n--- Tim kiem & Tinh toan ---" << endl;
    cout << "Tim Max (Me Phai): " << TimMax(t) << endl;
    cout << "Tim Min (Me Trai): " << TimMin(t) << endl;
    cout << "Chieu cao cay: " << ChieuCao(t) << endl;
    cout << "Tong gia tri cac node: " << Sum(t) << endl;

    cout << "\n--- Dem & Liet ke ---" << endl;
    cout << "Tong so node: " << DemNode(t) << endl;
    cout << "So node la (0 con): " << DemNodeLa(t) << endl;
    cout << "Cac node 1 con: "; XuatNode1Con(t); cout << endl;
    cout << "Cac node 2 con: "; XuatNode2Con(t); cout << endl;

    cout << "\n--- Ham chuyen biet (SNT) ---" << endl;
    int dem_snt = 0;
    SoLuongSNT(t, dem_snt);
    cout << "So luong SNT trong cay: " << dem_snt << " (La 11, 35? Oh 35 ko phai. Chi co 11)" << endl; 
    // Test lại: KiemTraSNT(11) = true. KiemTraSNT(35) = false. Đúng!

    int min_snt_tim_duoc = 999999;
    SNTNhoNhat(t, min_snt_tim_duoc);
    cout << "SNT nho nhat: " << min_snt_tim_duoc << endl;

    cout << "\n--- Test Xoa Node ---" << endl;
    // Test xóa "Lá rụng" (xóa 20)
    cout << "Xoa node 20 (La)..." << endl;
    XoaNode(t, 20);
    cout << "Cay LNR sau khi xoa 20: "; Xuat_LNR(t); cout << endl;

    // Test xóa "Gãy cành" (xóa 30, có 2 con, à không, xóa 20 rồi, 30 chỉ còn 1 con 40)
    // Ồ, node 20 có con 11. Vậy xóa 20 là trường hợp "Gãy cành" (1 con).
    // Hãy chạy lại logic:
    /*
                50
              /    \
             30     70
            /  \   /  \
           20  40 60  80
          /   /
         11  35 
    */
    // Xóa 20 (Case 1 con trái):
    // Cây sẽ thành:
    /*
                50
              /    \
             30     70
            /  \   /  \
           11  40 60  80
               /
              35 
    */
    cout << "Xoa node 30 (Case 2 con)..." << endl;
    XoaNode(t, 30);
    /* Xóa 30 (Case 2 con).
       Tìm người thế mạng: Cây con phải là (40, 35). Con trái nhất là 35.
       Data của 30 đổi thành 35.
       Xóa node 35 (lá) ở cây con phải.
       Cây sẽ thành:
                50
              /    \
             35     70
            /  \   /  \
           11  40 60  80 
    */
    cout << "Cay LNR sau khi xoa 30: "; Xuat_LNR(t); cout << endl;
    
    // Test xóa Gốc (Case 2 con)
    cout << "Xoa node 50 (Goc, Case 2 con)..." << endl;
    XoaNode(t, 50);
    /*
       Xóa 50.
       Tìm người thế mạng: Cây con phải là (70, 60, 80). Con trái nhất là 60.
       Data của 50 đổi thành 60.
       Xóa node 60 (lá) ở cây con phải.
       Cây sẽ thành:
                60
              /    \
             35     70
            /  \      \
           11  40     80 
    */
    cout << "Cay LNR sau khi xoa GOC 50: "; Xuat_LNR(t); cout << endl;
    cout << "Goc moi la: " << t->data << endl;

    return 0;
}