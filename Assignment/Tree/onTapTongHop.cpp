/*
 * TỆP ÔN TẬP CẤU TRÚC DỮ LIỆU CÂY NHỊ PHÂN
 * Ghi chú: Chúng ta sẽ giả định đang làm việc với Cây Nhị Phân Tìm Kiếm (BST)
 * để các hàm ThemNode, TimKiem, TimMax/Min, XoaNode có ý nghĩa nhất.
 */

#include <iostream>
#include <math.h> // Dùng cho KiemTraSNT, ktSoChinhPhuong
#include <queue>  // Dùng cho duyệt theo chiều rộng (nếu cần)

using namespace std;

// === PHẦN 1: NỀN MÓNG (VIÊN GẠCH) ===

/*
 * Cấu trúc Node: "Viên gạch" cơ bản
 * Tưởng tượng nó là một "viên gạch" có 3 phần:
 * 1. (data): Giá trị nó chứa (xi măng).
 * 2. (pleft): Sợi dây bên TRÁI để nối với viên gạch khác.
 * 3. (pright): Sợi dây bên PHẢI để nối với viên gạch khác.
 */
struct Node {
    int data;
    Node *pleft;
    Node *pright;
};

/*
 * Typedef (Đặt bí danh):
 * "Thay vì gọi dài dòng 'Node *' (con trỏ trỏ đến Node),
 * tôi sẽ đặt cho nó một cái tên thân mật là 'TREE'."
 * Từ giờ, TREE == Node*
 * Chúng ta dùng 'TREE' để chỉ "nút GỐC" (root) của một cái cây.
 */
typedef Node *TREE;

// --- HÀM 1.1: Khởi tạo Cây (Init) ---
/*
 * Mục đích: "Chuẩn bị" một mảnh đất trống để xây cây.
 * Logic: Cho con trỏ GỐC (t) trỏ vào NULL.
 * NULL = "không có gì", "cây rỗng", "mảnh đất trống".
 * Dùng tham chiếu (TREE &t) vì ta muốn THAY ĐỔI TRỰC TIẾP giá trị của t.
 */
void Init(TREE &t) {
    t = NULL;
}

// --- HÀM 1.2: Tạo Nút Mới (CreateNewNode) ---
/*
 * Mục đích: "Đúc" một "viên gạch" (Node) mới.
 * Logic:
 * 1. Dùng 'new' để xin hệ điều hành cấp phát một ô nhớ cho Node.
 * 2. Gán giá trị 'x' vào 'data'.
 * 3. Cho 2 sợi dây 'pleft' và 'pright' trỏ vào NULL (vì nó mới, chưa nối với ai).
 * 4. Trả về địa chỉ của viên gạch vừa đúc.
 */
Node* CreateNewNode(int x) {
    Node *p = new Node;
    if (p == NULL) {
        cout << "Loi: Khong du bo nho!" << endl;
        return NULL;
    }
    p->data = x;       // Đổ "xi măng" (giá trị x) vào
    p->pleft = NULL;   // Dây TRÁI chưa nối
    p->pright = NULL;  // Dây PHẢI chưa nối
    return p;          // Giao "viên gạch" cho người gọi
}

// === PHẦN 2: XÂY DỰNG & QUAN SÁT ===

// --- HÀM 2.1: Thêm Node Vào Cây (ThemNodeVaoCay) ---
/*
 * Mục đích: Thêm "viên gạch" (Node) có giá trị 'x' vào cây.
 * Logic (Giả định là Cây Nhị Phân Tìm Kiếm - BST):
 * Kỹ thuật gợi nhớ: "Lớn qua Phải, Nhỏ qua Trái"
 * 1. (t == NULL): Nếu cây rỗng, "viên gạch" mới chính là gốc.
 * 2. (x < t->data): Nếu 'x' NHỎ hơn nút hiện tại -> đi tìm chỗ trống bên TRÁI (đệ quy t->pleft).
 * 3. (x > t->data): Nếu 'x' LỚN hơn nút hiện tại -> đi tìm chỗ trống bên PHẢI (đệ quy t->pright).
 * 4. (x == t->data): Không làm gì (BST không lưu khóa trùng).
 * Dùng tham chiếu (TREE &t) vì có thể ta cần THAY ĐỔI GỐC (nếu cây rỗng).
 */
void ThemNodeVaoCay(TREE &t, int x) {
    // 1. Nếu đất trống (t == NULL)
    if (t == NULL) {
        t = CreateNewNode(x); // Đặt viên gạch mới làm móng (gốc)
    }
    // 2. Nếu đất đã có móng (t != NULL)
    else {
        // 2a. "Nhỏ qua Trái"
        if (x < t->data) {
            ThemNodeVaoCay(t->pleft, x);
        }
        // 2b. "Lớn qua Phải"
        else if (x > t->data) {
            ThemNodeVaoCay(t->pright, x);
        }
    }
}

// --- HÀM 2.2: Nhập Cây (Nháp) ---
/*
 * Mục đích: Nhập 'n' node từ bàn phím.
 */
void Nhap(TREE &t, int n) {
    cout << "Nhap " << n << " gia tri node: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ThemNodeVaoCay(t, x);
    }
}

// --- HÀM 2.3: Đọc File (Doc_file) ---
/*
 * Mục đích: Đọc các số từ file văn bản và thêm vào cây.
 * Giả sử file "input.txt" chỉ chứa các số nguyên.
 */
void Doc_file(char *tenFile, TREE &t) {
    FILE *f = fopen(tenFile, "r");
    if (f == NULL) {
        cout << "Loi: Khong mo duoc file " << tenFile << endl;
        return;
    }

    int x;
    // Đọc từng số (fscanf) cho đến khi hết file (EOF - End Of File)
    while (fscanf(f, "%d", &x) != EOF) {
        ThemNodeVaoCay(t, x); // Thêm số vừa đọc vào cây
    }

    fclose(f); // Đóng file sau khi dùng xong
    cout << "Da doc file va tao cay thanh cong!" << endl;
}


// --- HÀM 2.4 (Nhóm): Các Phép Duyệt Cây (Traversal) ---
/*
 * Mục đích: "In" cây ra màn hình để xem.
 * Kỹ thuật gợi nhớ: Vị trí của "N" (Nút - Node) quyết định tên gọi!
 * "N": Thăm (in ra) nút hiện tại (t->data).
 * "L": Đệ quy (đi thăm) cây con TRÁI (t->pleft).
 * "R": Đệ quy (đi thăm) cây con PHẢI (t->pright).
 */

// 2.4a: Xuất NLR (PreOrder - Duyệt TIỀN tự)
/*
 * Kỹ thuật gợi nhớ: "N-gay" -> "L-òng vòng" -> "R-ẽ phải"
 * (Thăm Nút "N-gay", rồi đi "L-òng vòng" bên Trái, cuối cùng "R-ẽ phải")
 * Thứ tự: Thăm "N" -> Đi "L" -> Đi "R"
 */
void Xuat_NLR(TREE t) {
    if (t != NULL) {
        cout << t->data << " "; // "N" - Thăm Nút (Gốc)
        Xuat_NLR(t->pleft);   // "L" - Thăm con Trái
        Xuat_NLR(t->pright);  // "R" - Thăm con Phải
    }
}

// 2.4b: Xuất LNR (InOrder - Duyệt TRUNG tự)
/*
 * Kỹ thuật gợi nhớ: "Chờ L-âu" -> "thăm N-ó" -> "R-ẽ riêng"
 * (Đi hết bên Trái "L-âu", mới "thăm N-ó", cuối cùng "R-ẽ riêng" qua Phải)
 * Thứ tự: Đi "L" -> Thăm "N" -> Đi "R"
 * ** QUAN TRỌNG: LNR trên BST sẽ cho ra dãy số TĂNG DẦN **
 */
void Xuat_LNR(TREE t) {
    if (t != NULL) {
        Xuat_LNR(t->pleft);   // "L" - Thăm con Trái
        cout << t->data << " "; // "N" - Thăm Nút (Gốc)
        Xuat_LNR(t->pright);  // "R" - Thăm con Phải
    }
}

// 2.4c: Xuất LRN (PostOrder - Duyệt HẬU tự)
/*
 * Kỹ thuật gợi nhớ: "L-òng vòng" -> "R-ẽ riêng" -> "thăm N-ó (cuối)"
 * (Đi hết bên Trái "L-òng vòng", "R-ẽ riêng" qua Phải, cuối cùng mới "thăm N-ó")
 * Thứ tự: Đi "L" -> Đi "R" -> Thăm "N"
 */
void Xuat_LRN(TREE t) {
    if (t != NULL) {
        Xuat_LRN(t->pleft);   // "L" - Thăm con Trái
        Xuat_LRN(t->pright);  // "R" - Thăm con Phải
        cout << t->data << " "; // "N" - Thăm Nút (Gốc)
    }
}

// 2.4d,e,f: Các biến thể duyệt (NRL, RNL, RLN)
// Logic y hệt, chỉ đảo thứ tự gọi đệ quy.
void Xuat_NRL(TREE t) {
    if (t != NULL) {
        cout << t->data << " "; // "N"
        Xuat_NRL(t->pright);  // "R"
        Xuat_NRL(t->pleft);   // "L"
    }
}
void Xuat_RNL(TREE t) {
    if (t != NULL) {
        Xuat_RNL(t->pright);  // "R"
        cout << t->data << " "; // "N"
        Xuat_RNL(t->pleft);   // "L"
        // (Duyệt RNL trên BST sẽ cho dãy GIẢM DẦN)
    }
}
void Xuat_RLN(TREE t) {
    if (t != NULL) {
        Xuat_RLN(t->pright);  // "R"
        Xuat_RLN(t->pleft);   // "L"
        cout << t->data << " "; // "N"
    }
}


// === PHẦN 3: TÌM KIẾM & ĐO LƯỜNG ===

// --- HÀM 3.1: Tìm Kiếm (TimKiem) ---
/*
 * Mục đích: Tìm xem node có giá trị 'x' có trong cây BST không.
 * Logic: Y hệt hàm ThemNodeVaoCay!
 * Kỹ thuật gợi nhớ: "Lớn qua Phải, Nhỏ qua Trái"
 * 1. (t == NULL): Cây rỗng -> Không tìm thấy (return NULL).
 * 2. (x < t->data): 'x' NHỎ hơn -> đi tìm bên TRÁI.
 * 3. (x > t->data): 'x' LỚN hơn -> đi tìm bên PHẢI.
 * 4. (x == t->data): Tìm thấy! Trả về chính nút 't' đó.
 */
Node* TimKiem(TREE t, int x) {
    if (t == NULL) {
        return NULL; // Hết đường, không thấy
    }

    if (x < t->data) {
        return TimKiem(t->pleft, x); // "Nhỏ qua Trái"
    } else if (x > t->data) {
        return TimKiem(t->pright, x); // "Lớn qua Phải"
    } else { // x == t->data
        return t; // Tìm thấy!
    }
}

// --- HÀM 3.2: Tìm Max (TimMax) ---
/*
 * Mục đích: Tìm node có giá trị LỚN NHẤT trong BST.
 * Kỹ thuật gợi nhớ: "Max thì Mê Phải"
 * Logic: Trong BST, node lớn nhất luôn nằm ở "tận cùng bên PHẢI".
 * Cứ đi sang phải (t->pright) cho đến khi (t->pright == NULL) thì dừng.
 */
int TimMax(TREE t) {
    if (t == NULL) return -1; // Cây rỗng

    // Nếu con phải là NULL -> nó là tận cùng bên phải -> nó là Max
    if (t->pright == NULL) {
        return t->data;
    }
    // Nếu chưa, tiếp tục "Mê Phải"
    return TimMax(t->pright);
}

// --- HÀM 3.3: Tìm Min (TimMin) ---
/*
 * Mục đích: Tìm node có giá trị NHỎ NHẤT trong BST.
 * Kỹ thuật gợi nhớ: "Min thì Mê Trái"
 * Logic: Trong BST, node nhỏ nhất luôn nằm ở "tận cùng bên TRÁI".
 * Cứ đi sang trái (t->pleft) cho đến khi (t->pleft == NULL) thì dừng.
 */
int TimMin(TREE t) {
    if (t == NULL) return -1; // Cây rỗng

    // Nếu con trái là NULL -> nó là tận cùng bên trái -> nó là Min
    if (t->pleft == NULL) {
        return t->data;
    }
    // Nếu chưa, tiếp tục "Mê Trái"
    return TimMin(t->pleft);
}

// --- HÀM 3.4 (Nhóm): Các Hàm "Đo Lường" (Measure) ---
/*
 * Logic chung của các hàm này là Đệ Quy:
 * "Kết quả (Cha) = Xử lý (Cha) + Kết quả (Con Trái) + Kết quả (Con Phải)"
 */

// 3.4a: Đếm Node (DemNode)
/*
 * Logic: "Tổng số node = 1 (là nó) + Tổng số node (con trái) + Tổng số node (con phải)"
 */
int DemNode(TREE t) {
    if (t == NULL) {
        return 0; // Cây rỗng có 0 nút
    }
    return 1 + DemNode(t->pleft) + DemNode(t->pright);
}

// 3.4b: Đếm Node Lá (DemNodeLa / xuat_cay_0_con)
/*
 * Logic: Lá là node "0 con" (pleft == NULL VÀ pright == NULL).
 */
int DemNodeLa(TREE t) {
    if (t == NULL) {
        return 0; // Rỗng, không có lá
    }
    // Nếu nó là lá (0 con)
    if (t->pleft == NULL && t->pright == NULL) {
        return 1; // Đếm là 1
    }
    // Nếu không phải lá, đi tìm lá ở 2 con
    return DemNodeLa(t->pleft) + DemNodeLa(t->pright);
}
// Hàm xuất node 0 con (lá)
void XuatNodeLa(TREE t) {
    if (t == NULL) return;
    if (t->pleft == NULL && t->pright == NULL) {
        cout << t->data << " ";
    }
    XuatNodeLa(t->pleft);
    XuatNodeLa(t->pright);
}

// 3.4c: Tính Chiều Cao (ChieuCao)
/*
 * Logic: "Chiều cao = 1 (là nó) + Max(Chiều cao(con trái), Chiều cao(con phải))"
 * (Lấy đứa con cao hơn, rồi cộng thêm 1)
 */
int ChieuCao(TREE t) {
    if (t == NULL) {
        return 0; // Cây rỗng (hoặc lá) thì không cao
    }
    int h_left = ChieuCao(t->pleft);   // Chiều cao con trái
    int h_right = ChieuCao(t->pright); // Chiều cao con phải
    return 1 + max(h_left, h_right);
}

// 3.4d: Tính Tổng (Sum)
/*
 * Logic: "Tổng = data (của nó) + Tổng (con trái) + Tổng (con phải)"
 */
int Sum(TREE t) {
    if (t == NULL) {
        return 0; // Cây rỗng có tổng = 0
    }
    return t->data + Sum(t->pleft) + Sum(t->pright);
}

// 3.4e: Tìm Cấp (Level) của Node (level_max / level_min)
/*
 * Để tìm "level_max", ta cần tìm level (cấp) của node `TimMax(t)`.
 * Logic: Viết 1 hàm `TimLevelCuaNode(t, x, current_level)`
 */
int TimLevelCuaNode(TREE t, int x, int current_level) {
    if (t == NULL) {
        return 0; // Không tìm thấy
    }
    if (t->data == x) {
        return current_level; // Tìm thấy! Trả về cấp hiện tại
    } else if (x < t->data) {
        return TimLevelCuaNode(t->pleft, x, current_level + 1); // Đi tìm bên trái, cấp + 1
    } else {
        return TimLevelCuaNode(t->pright, x, current_level + 1); // Đi tìm bên phải, cấp + 1
    }
}


// === PHẦN 4: LỌC DỮ LIỆU & KIỂM TRA TÍNH CHẤT ===

// --- HÀM 4.1: Xuất Node 1 con (xuat_cay_1_con) ---
/*
 * Logic: Duyệt cây (NLR). Tại mỗi nút, kiểm tra điều kiện "1 con".
 * Điều kiện 1 con: (Trái CÓ, Phải KHÔNG) HOẶC (Trái KHÔNG, Phải CÓ)
 * Kỹ thuật gợi nhớ: Đây là phép "XOR" logic.
 */
void XuatNode1Con(TREE t) {
    if (t == NULL) return;

    // Điều kiện XOR: (A && !B) || (!A && B)
    if ((t->pleft != NULL && t->pright == NULL) || (t->pleft == NULL && t->pright != NULL)) {
        cout << t->data << " ";
    }
    
    // Tiếp tục tìm ở 2 con
    XuatNode1Con(t->pleft);
    XuatNode1Con(t->pright);
}

// --- HÀM 4.2: Xuất Node 2 con (xuat_cay_2_con) ---
/*
 * Logic: Duyệt cây (NLR). Tại mỗi nút, kiểm tra điều kiện "2 con".
 * Điều kiện 2 con: (Trái CÓ) VÀ (Phải CÓ)
 */
void XuatNode2Con(TREE t) {
    if (t == NULL) return;

    if (t->pleft != NULL && t->pright != NULL) {
        cout << t->data << " ";
    }
    
    XuatNode2Con(t->pleft);
    XuatNode2Con(t->pright);
}

// --- HÀM 4.3 (Nhóm): Số Nguyên Tố (SNT) ---
bool KiemTraSNT(int x) {
    if (x < 2) return false; // SNT phải >= 2
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) return false; // Chia hết -> không phải SNT
    }
    return true; // Không chia hết cho ai -> là SNT
}

// Đếm số lượng SNT. Dùng tham chiếu `&dem` để "mang" kết quả đếm ra ngoài.
void SoLuongSNT(TREE t, int &dem) {
    if (t != NULL) {
        // Xử lý nút hiện tại
        if (KiemTraSNT(t->data)) {
            dem++;
        }
        // Đệ quy 2 con
        SoLuongSNT(t->pleft, dem);
        SoLuongSNT(t->pright, dem);
    }
}

// Tìm SNT nhỏ nhất. Dùng tham chiếu `&min_snt`
// (Khi gọi, truyền vào giá trị `min_snt` ban đầu rất lớn)
void SNTNhoNhat(TREE t, int &min_snt) {
    if (t != NULL) {
        if (KiemTraSNT(t->data) && t->data < min_snt) {
            min_snt = t->data; // Cập nhật min
        }
        SNTNhoNhat(t->pleft, min_snt);
        SNTNhoNhat(t->pright, min_snt);
    }
}

// --- HÀM 4.4 (Nhóm): Số Chính Phương (SCP) ---
bool KtSoChinhPhuong(int n) {
    if (n < 0) return false;
    int root = (int)sqrt(n); // Lấy căn bậc 2 (phần nguyên)
    return (root * root == n); // Bình phương lên xem có bằng 'n' không
}

// Tìm SCP lớn nhất. Dùng tham chiếu `&max_scp`
// (Khi gọi, truyền vào giá trị `max_scp` ban đầu rất nhỏ)
void SoChinhPhuongLonNhat(TREE t, int &max_scp) {
    if (t != NULL) {
        if (KtSoChinhPhuong(t->data) && t->data > max_scp) {
            max_scp = t->data; // Cập nhật max
        }
        SoChinhPhuongLonNhat(t->pleft, max_scp);
        SoChinhPhuongLonNhat(t->pright, max_scp);
    }
}

// --- HÀM 4.5: Đếm Node bằng X (demSoNodeBangX) ---
/*
 * Mục đích: Đếm số node có giá trị bằng 'x'.
 * Logic (BST Tối ưu): Vì BST không lưu trùng, ta chỉ cần ĐI TÌM 'x'.
 * Nếu thấy -> return 1. Nếu không thấy -> return 0.
 */
int DemSoNodeBangX(TREE t, int x) {
    if (t == NULL) {
        return 0; // Hết đường, không thấy
    }
    if (x < t->data) {
        return DemSoNodeBangX(t->pleft, x);
    } else if (x > t->data) {
        return DemSoNodeBangX(t->pright, x);
    } else { // x == t->data
        return 1; // Tìm thấy!
    }
    // (Nếu là CÂY THƯỜNG, logic sẽ là:
    // int dem = (t->data == x) ? 1 : 0;
    // return dem + DemSoNodeBangX(t->pleft, x) + DemSoNodeBangX(t->pright, x);
    // )
}


// === PHẦN 5: THAO TÁC (XÓA NODE) ===
// Kỹ thuật gợi nhớ: "Xóa Node" có 3 trường hợp:
// 1. "Lá rụng": Node cần xóa là lá (0 con) -> Xóa luôn.
// 2. "Gãy cành, nối thân": Node cần xóa có 1 con -> Nối con nó vào ông nội nó.
// 3. "Tìm người thế mạng": Node cần xóa có 2 con -> Khó nhất!
//    -> Tìm 1 người "thế mạng" (substitute) cho nó.


// --- HÀM 5.1 (Helper): Tìm Node Thế Mạng ---
/*
 * Mục đích: Tìm người "thế mạng" cho node có 2 con.
 * Kỹ thuật gợi nhớ: "Vua truyền ngôi cho Con Phải, Con Phải nhường cho Em Út (con trái nhất)".
 * Logic: Tìm node "Con Trái Nhất của Cây Con Phải".
 * (Hoặc "Con Phải Nhất của Cây Con Trái" - ta chọn 1 cách)
 *
 * `node_the_mang`: ban đầu là `t->pright` (Cây con Phải)
 * `node_can_xoa`: là node `t` (node có 2 con cần xóa)
 */
void TimNodeTheMang(TREE &node_the_mang, TREE &node_can_xoa) {
    // 1. "Mê Trái": Cứ đi sang trái (pleft)
    if (node_the_mang->pleft != NULL) {
        TimNodeTheMang(node_the_mang->pleft, node_can_xoa);
    }
    // 2. Đã đến "tận cùng bên trái" (`node_the_mang` là con trái nhất)
    else {
        // 2a. "Đánh cắp" data:
        //    Gán data của người thế mạng cho data của nút cần xóa
        node_can_xoa->data = node_the_mang->data;
        
        // 2b. "Thủ tiêu" người thế mạng:
        Node *temp = node_the_mang; // Giữ lại người thế mạng để free
        // Nối con phải của người thế mạng (nếu có) vào cha nó
        node_the_mang = node_the_mang->pright;
        
        delete temp; // Xóa người thế mạng
    }
}

// --- HÀM 5.2: Xóa Node (XoaNode) ---
/*
 * Mục đích: Xóa node có giá trị 'x' khỏi cây.
 * Dùng tham chiếu (TREE &t) vì ta THAY ĐỔI cấu trúc cây (nối lại dây).
 */
void XoaNode(TREE &t, int x) {
    if (t == NULL) {
        return; // Cây rỗng, không có gì để xóa
    }

    // Bước 1: ĐI TÌM NODE CẦN XÓA (giống hàm TimKiem)
    if (x < t->data) {
        XoaNode(t->pleft, x); // Đi tìm bên trái
    } else if (x > t->data) {
        XoaNode(t->pright, x); // Đi tìm bên phải
    }
    // Bước 2: ĐÃ TÌM THẤY (x == t->data). `t` là nút cần xóa.
    else {
        Node *node_bi_xoa = t; // Giữ lại để free

        // Case 1: "Lá rụng" (0 con)
        if (t->pleft == NULL && t->pright == NULL) {
            t = NULL; // Cha trỏ vào NULL
        }
        // Case 2: "Gãy cành" (1 con)
        // 2a. Chỉ có con PHẢI
        else if (t->pleft == NULL) {
            t = t->pright; // Cha trỏ vào con phải
        }
        // 2b. Chỉ có con TRÁI
        else if (t->pright == NULL) {
            t = t->pleft; // Cha trỏ vào con trái
        }
        // Case 3: "Tìm người thế mạng" (2 con)
        else {
            // Tìm người thế mạng ở "Cây con Phải"
            TimNodeTheMang(t->pright, t);
        }
        
        // Chỉ delete `node_bi_xoa` nếu nó không phải là Case 3
        // (Vì Case 3 đã tự delete `temp` bên trong)
        if (node_bi_xoa == t) {
            delete node_bi_xoa;
        }
    }
}

// --- HÀM 5.3: Xóa Node 1 con và Node Lá (xoaNode1ConVaNodeLa) ---
/*
 * Mục đích: Xóa node 'x' CHỈ KHI nó là node 1 con hoặc node lá.
 * Logic:
 * 1. Tìm node 'x' (giống TimKiem).
 * 2. Khi tìm thấy (t->data == x), kiểm tra xem nó có phải 1 con hoặc lá không.
 * 3. Nếu ĐÚNG, gọi hàm XoaNode(t, x).
 * 4. Nếu SAI (nó là node 2 con), thì KHÔNG LÀM GÌ.
 *
 * Ghi chú: Hàm này trong đề của bạn (ảnh) có prototype là
 * `void xoaNode1ConVaNodeLa(TREE &t, int x);`
 * Tôi sẽ cài đặt theo prototype này.
 */
void XoaNode1ConVaNodeLa(TREE &t, int x) {
    // Bước 1: Tìm node 'x'
    Node *node_can_xoa = TimKiem(t, x);

    // Bước 2: Kiểm tra xem có tìm thấy không
    if (node_can_xoa == NULL) {
        cout << "[XoaNode1ConVaNodeLa] Khong tim thay " << x << endl;
        return; // Không tìm thấy, không làm gì
    }

    // Bước 3: Kiểm tra điều kiện (0 con hoặc 1 con)
    bool la_node_la = (node_can_xoa->pleft == NULL && node_can_xoa->pright == NULL);
    bool la_node_1_con = ((node_can_xoa->pleft != NULL && node_can_xoa->pright == NULL) ||
                        (node_can_xoa->pleft == NULL && node_can_xoa->pright != NULL));

    // Bước 4: Nếu là 0 con hoặc 1 con -> Xóa
    if (la_node_la || la_node_1_con) {
        cout << "[XoaNode1ConVaNodeLa] Xoa " << x << " (vi la node 0/1 con)" << endl;
        XoaNode(t, x); // Gọi hàm xóa "xịn"
    } else {
        // Ngược lại (là node 2 con) -> Không làm gì
        cout << "[XoaNode1ConVaNodeLa] Khong xoa " << x << " (vi la node 2 con)" << endl;
    }
}


//==================================================//
// ===         PHÒNG THÍ NGHIỆM (main)          === //
//==================================================//
int main() {
    TREE t; // Tạo "mảnh đất" t

    // === Test 1: Khởi tạo & Thêm Node ===
    cout << "--- Test 1: Init & ThemNodeVaoCay ---" << endl;
    Init(t); // Làm sạch mảnh đất
    
    // Thêm các node (đây là cây chúng ta sẽ dùng để test)
    ThemNodeVaoCay(t, 50);
    ThemNodeVaoCay(t, 30);
    ThemNodeVaoCay(t, 70);
    ThemNodeVaoCay(t, 20);
    ThemNodeVaoCay(t, 40);
    ThemNodeVaoCay(t, 60);
    ThemNodeVaoCay(t, 80);
    ThemNodeVaoCay(t, 11); // Thêm SNT
    ThemNodeVaoCay(t, 36); // Thêm SCP
    ThemNodeVaoCay(t, 49); // Thêm SNT (không phải) và SCP
    ThemNodeVaoCay(t, 9);  // Thêm SCP

    /* Cây của chúng ta sẽ trông như thế này:
              50
            /    \
           30     70
          /  \   /  \
         20  40 60  80
        /   / \
       11  36 49
      /
     9 
    */
    cout << "[INFO] Da them 11 node vao cay." << endl;

    // === Test 2: Duyệt Cây (Quan sát) ===
    cout << "\n--- Test 2: Duyet Cay (De kiem tra Test 1) ---" << endl;
    cout << "Duyet LNR (phai TANG DAN): "; Xuat_LNR(t); cout << endl;
    cout << "Duyet NLR (PreOrder):    "; Xuat_NLR(t); cout << endl;
    cout << "Duyet LRN (PostOrder):   "; Xuat_LRN(t); cout << endl;
    cout << "Duyet NRL:               "; Xuat_NRL(t); cout << endl;
    cout << "Duyet RNL (phai GIAM DAN):"; Xuat_RNL(t); cout << endl;
    cout << "Duyet RLN:               "; Xuat_RLN(t); cout << endl;

    // === Test 3: Tìm Kiếm & Đo Lường ===
    cout << "\n--- Test 3: Tim Kiem & Do Luong ---" << endl;
    // Test TimKiem
    cout << "Tim 40: " << (TimKiem(t, 40) ? "Tim thay" : "Khong thay") << " (Chuan: Tim thay)" << endl;
    cout << "Tim 99: " << (TimKiem(t, 99) ? "Tim thay" : "Khong thay") << " (Chuan: Khong thay)" << endl;
    
    // Test TimMax / TimMin
    cout << "Tim Max (Me Phai): " << TimMax(t) << " (Chuan: 80)" << endl;
    cout << "Tim Min (Me Trai): " << TimMin(t) << " (Chuan: 9)" << endl;
    
    // Test DemNode / DemNodeLa / ChieuCao / Sum
    cout << "Tong so Node: " << DemNode(t) << " (Chuan: 11)" << endl;
    cout << "So Node La (0 con): " << DemNodeLa(t) << " (La: 9, 36, 49, 60, 80 -> Chuan: 5)" << endl;
    cout << "Chieu cao cay: " << ChieuCao(t) << " (Goc la 1)" << endl;
    cout << "Tong gia tri Node: " << Sum(t) << endl;

    // Test TimLevel (level_max / level_min)
    int max_val = TimMax(t);
    int min_val = TimMin(t);
    cout << "Level cua Max (80): " << TimLevelCuaNode(t, max_val, 1) << " (Chuan: 3)" << endl;
    cout << "Level cua Min (9):  " << TimLevelCuaNode(t, min_val, 1) << " (Chuan: 5)" << endl;


    // === Test 4: Lọc Dữ Liệu & Tính Chất ===
    cout << "\n--- Test 4: Loc Du Lieu & Tinh Chat ---" << endl;
    cout << "Cac Node 0 con (La): "; XuatNodeLa(t); cout << endl;
    cout << "Cac Node 1 con: "; XuatNode1Con(t); cout << " (Chuan: 11, 20, 40, 70)" << endl;
    cout << "Cac Node 2 con: "; XuatNode2Con(t); cout << " (Chuan: 50, 30)" << endl;
    
    // Test SNT
    int dem_snt = 0;
    SoLuongSNT(t, dem_snt);
    cout << "So luong SNT: " << dem_snt << " (SNT: 11. Chuan: 1)" << endl;
    int min_snt = 999999;
    SNTNhoNhat(t, min_snt);
    cout << "SNT nho nhat: " << min_snt << " (Chuan: 11)" << endl;
    
    // Test SCP
    int max_scp = -1; // -1 vì 0 cũng là SCP
    SoChinhPhuongLonNhat(t, max_scp);
    cout << "SCP lon nhat: " << max_scp << " (SCP: 9, 36, 49. Chuan: 49)" << endl;
    
    // Test DemSoNodeBangX
    cout << "So luong node co gia tri 40: " << DemSoNodeBangX(t, 40) << " (Chuan: 1)" << endl;
    cout << "So luong node co gia tri 99: " << DemSoNodeBangX(t, 99) << " (Chuan: 0)" << endl;

    // === Test 5: Thao Tác Xóa Node ===
    cout << "\n--- Test 5: Xoa Node (Kho Nhat) ---" << endl;
    cout << "Cay truoc khi xoa (LNR): "; Xuat_LNR(t); cout << endl;
    
    // Test 5.1: XoaNode1ConVaNodeLa
    // Xóa 50 (là node 2 con) -> Sẽ KHÔNG xóa
    XoaNode1ConVaNodeLa(t, 50);
    // Xóa 80 (là node lá) -> Sẽ XÓA
    XoaNode1ConVaNodeLa(t, 80);
    cout << "Cay sau khi [XoaNode1ConVaNodeLa] (LNR): "; Xuat_LNR(t); cout << endl;
    
    // Test 5.2: Xóa Node 1 con (XoaNode) -> Xóa 20 (chỉ có con 11)
    cout << "Test XoaNode: Xoa 20 (1 con)..." << endl;
    XoaNode(t, 20);
    cout << "Cay sau khi xoa 20 (LNR): "; Xuat_LNR(t); cout << endl;

    // Test 5.3: Xóa Node 2 con (XoaNode) -> Xóa 30 (có 11 và 40)
    cout << "Test XoaNode: Xoa 30 (2 con)..." << endl;
    XoaNode(t, 30);
    /* Ai sẽ thế mạng 30?
       Cây con phải là (40, 36, 49).
       Con Trái Nhất của Cây Con Phải là... 36.
       -> 30 sẽ bị đổi data thành 36. Node 36 gốc sẽ bị xóa (là lá).
    */
    cout << "Cay sau khi xoa 30 (LNR): "; Xuat_LNR(t); cout << endl;
    
    // Test 5.4: Xóa Gốc (2 con) -> Xóa 50
    cout << "Test XoaNode: Xoa 50 (Goc, 2 con)..." << endl;
    XoaNode(t, 50);
    /* Ai sẽ thế mạng 50?
       Cây con phải là (70, 60).
       Con Trái Nhất của Cây Con Phải là... 60.
       -> 50 sẽ bị đổi data thành 60. Node 60 gốc sẽ bị xóa (là lá).
    */
    cout << "Cay sau khi xoa GOC 50 (LNR): "; Xuat_LNR(t); cout << endl;
    cout << "Goc moi cua cay la: " << t->data << " (Chuan: 60)" << endl;

    // === Test 6: Đọc File (Doc_file) ===
    /*
    cout << "\n--- Test 6: Doc File ---" << endl;
    TREE t_file;
    Init(t_file);
    // BƯỚC 1: Bạn hãy tạo 1 file tên "input.txt"
    // BƯỚC 2: Gõ vào file đó các số: 10 5 15 3 7
    // BƯỚC 3: Bỏ comment 2 dòng dưới đây và chạy
    // Doc_file((char*)"input.txt", t_file);
    // cout << "Duyet LNR cay doc tu file: "; Xuat_LNR(t_file); cout << endl;
    */

    cout << "\n[SUCCESS] Chuc mung ban da hoan thanh bai kiem tra!" << endl;

    return 0;
}