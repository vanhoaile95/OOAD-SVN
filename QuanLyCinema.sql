CREATE DATABASE QuanLyCinema

USE QuanLyCinema

/*LƯU Ý: 
	mình chỉ làm cho phim 2D thôi ko có 3D, 
	nhân viên của mình tất cả là part-time lương theo giờ (20k/giờ) lương lấy trong bàng chức vụ
	riêng nhân viên cao cấp là làm full-time thì có lương tháng mặc định trong bảng chức vụ
*/

SET DATEFORMAT DMY

CREATE TABLE PHONGCHIEU
(
	MAPHONGCHIEU VARCHAR(20),
	PRIMARY KEY(MAPHONGCHIEU),
	TENPHONGCHIEU NVARCHAR(50),
	SOGHE INT,
	TINHTRANG NVARCHAR(50),---khi code nen de 2 trang thai: "Đang sử dụng", "Không sử dụng"
)

INSERT INTO PHONGCHIEU VALUES ('PC001',N'Phòng chiếu A',100,N'Đang sử dụng')
INSERT INTO PHONGCHIEU VALUES ('PC002',N'Phòng chiếu B',100,N'Đang sử dụng')
INSERT INTO PHONGCHIEU VALUES ('PC003',N'Phòng chiếu C',100,N'Không sử dụng')

CREATE TABLE PHIM
(
	MAPHIM VARCHAR(20),
	PRIMARY KEY(MAPHIM),
	TENPHIM NVARCHAR(200),
	CONGNGHE VARCHAR(10), -- mặc định giá trị là 2D
	THELOAI NVARCHAR(200),
	QUOCGIA NVARCHAR(200),
	THOILUONG INT,
	DAODIEN NVARCHAR(200),
	DIENVIEN NVARCHAR(200),
	TINHTRANG NVARCHAR(50), -- 2 trạng thái: "Đang sử dụng", "Không sử dụng", "Đã xoá"
	CHITIET NVARCHAR(1000),
)

INSERT INTO PHIM VALUES ('PH001',N'Cô Hầu Gái','2D',N'Tâm lý - Tình cảm',N'Hàn Quốc',150,'Park Chan Wook','Kim Min Hee, Ha Jung-woo, Jo Jin Woong',N'Đang sử dụng',N'Phim Người Hầu Gái - The Handmaiden (2016): Diễn ra trong thời kì Hàn quốc đang là thuộc địa của Nhật (1910-1945). Một cô gái mồ côi được thuê bởi một người đàn ông để lấy được lòng tin của một người thừa kế nữ giàu có, nhưng cuối cùng lại phải lòng cô gái ấy.')
INSERT INTO PHIM VALUES ('PH002',N'Tiểu Đội Cò Bay','2D',N'Hài - Hoạt Hình',N'Mỹ',90,'Nicholas Stoller, Doug Sweetland','Andy Samberg, Kelsey Grammer',N'Đang sử dụng',N'Lấy nội dung từ những truyền thuyết cổ xưa, em bé được những chú cò mang đến cho bố mẹ trong bọc vải trẳng, STORKS là bộ phim hoạt hình hài hước nhưng không kém phần nhân văn với nội dung được khai thác độc đáo và thú vị về sự liên hệ giữa thế giới loài cò và con người.')
INSERT INTO PHIM VALUES ('PH003',N'Thảm Hoạ Giàn Khoan','2D',N'Tâm lý, Hành động, Ly kì',N'Mỹ',120,'Peter Berg','Mark Wahlberg, Kate Hudson',N'Đang sử dụng',N'Deepwater Horizon dựa trên một câu chuyện có thật kể về một nhóm thám hiểm tìm kiếm dầu từ đáy đại dương. Tuy nhiên, thứ họ tìm được dường như chưa từng được biết đến - một thứ dầu kỳ lạ. Cả nhóm tưởng như tìm được một nguồn nguyên liệu mới nhưng khi thứ dầu ấy khiến giàn khoan bốc cháy, họ biết tất cả chỉ mới bắt đầu.')

CREATE TABLE CT_PHIM
(
	MAPHIM VARCHAR(20),
	FOREIGN KEY (MAPHIM) REFERENCES PHIM(MAPHIM),
	PHIENBAN NVARCHAR(50), -- mặc định chỉ có 2 loại "Phụ đề", "Lồng tiếng"
	PRIMARY KEY (MAPHIM,PHIENBAN),
)

INSERT INTO CT_PHIM VALUES ('PH001',N'Lồng tiếng')
INSERT INTO CT_PHIM VALUES ('PH001',N'Phụ đề')
INSERT INTO CT_PHIM VALUES ('PH002',N'Lồng tiếng')
INSERT INTO CT_PHIM VALUES ('PH002',N'Phụ đề')
INSERT INTO CT_PHIM VALUES ('PH003',N'Phụ đề')



CREATE TABLE LICHCHIEU
(
	MALICHCHIEU VARCHAR(20),
	PRIMARY KEY(MALICHCHIEU),

	MAPHIM VARCHAR(20),
	PHIENBAN NVARCHAR(50), -- mặc định chỉ có 2 loại "Phụ đề", "Lồng tiếng"
	FOREIGN KEY (MAPHIM,PHIENBAN) REFERENCES CT_PHIM(MAPHIM,PHIENBAN),

	MAPHONGCHIEU VARCHAR(20),
	FOREIGN KEY (MAPHONGCHIEU) REFERENCES PHONGCHIEU(MAPHONGCHIEU),

	NGAYCHIEU SMALLDATETIME,
	GIOBATDAU VARCHAR(20),---lưu theo định dạng giờ, phút ví dụ: 5:30 => 5,30 hay 8:00 => 8,00
	GIOKETTHUC VARCHAR(20), -- hệ thống tự động tính ra = GIOBATDAU + THOILUONG (bảng PHIM),
	TINHTRANG NVARCHAR(50), --có 3 trạng thái: "Chưa chiếu", "Đã chiếu", "Đã huỷ"
)

INSERT INTO LICHCHIEU VALUES ('LC001','PH001',N'Lồng tiếng','PC001','1/10/2016','5,30','8,00',N'Đã chiếu')
INSERT INTO LICHCHIEU VALUES ('LC002','PH001',N'Phụ đề','PC001','1/10/2016','8,30','11,00',N'Đã chiếu')
INSERT INTO LICHCHIEU VALUES ('LC003','PH002',N'Lồng tiếng','PC002','1/10/2016','5,30','7,00',N'Đã chiếu')
INSERT INTO LICHCHIEU VALUES ('LC004','PH001',N'Lồng tiếng','PC001','5/11/2016','5,30','8,00',N'Chưa chiếu')
INSERT INTO LICHCHIEU VALUES ('LC005','PH001',N'Phụ đề','PC001','5/11/2016','8,30','11,00',N'Chưa chiếu')
INSERT INTO LICHCHIEU VALUES ('LC006','PH002',N'Lồng tiếng','PC002','5/11/2016','5,30','7,00',N'Chưa chiếu')
INSERT INTO LICHCHIEU VALUES ('LC007','PH002',N'Phụ đề','PC002','5/11/2016','7,30','10,00',N'Đã huỷ')
INSERT INTO LICHCHIEU VALUES ('LC008','PH003',N'Phụ đề','PC001','5/11/2016','5,30','7,30',N'Chưa chiếu')


CREATE TABLE VE
(
	MAVE VARCHAR(20),
	PRIMARY KEY(MAVE),

	MALICHCHIEU VARCHAR(20),
	FOREIGN KEY (MALICHCHIEU) REFERENCES LICHCHIEU(MALICHCHIEU),

	STTGHE INT, --số thứ tự ghế ngồi > 0 VÀ <= MAX GHẾ
)



CREATE TABLE CHUCVU -- cái này áp dụng cho nhân viên full time cấp cao, lương theo tháng
(
	MACHUCVU VARCHAR(20),
	PRIMARY KEY(MACHUCVU),
	TENCHUCVU NVARCHAR(50),
	LUONG INT,
)

INSERT INTO CHUCVU VALUES ('CV001',N'Quản lý',50000000) --lương tháng
INSERT INTO CHUCVU VALUES ('CV002',N'Thủ quỹ',20000000) --lương tháng
INSERT INTO CHUCVU VALUES ('CV003',N'Giám sát',20000000)--lương tháng
INSERT INTO CHUCVU VALUES ('CV004',N'Nhân viên',20000) -- lương theo giờ

CREATE TABLE NHANVIEN
(
	MANV VARCHAR(20),
	PRIMARY KEY(MANV),
	PASSWORD VARCHAR(50),
	HOTEN NVARCHAR(100),
	NGAYSINH SMALLDATETIME,	-- cần kiểm tra từ ngày sinh đến bây giờ đã đủ tuổi đi làm chưa (15 - 60 tuổi với nam, 15- 55 tuổi với nữ)
	GIOITINH NVARCHAR(10),

	MACHUCVU VARCHAR(20),
	FOREIGN KEY(MACHUCVU) REFERENCES CHUCVU(MACHUCVU),
	NGAYVAOLAM SMALLDATETIME,
	CMND VARCHAR(20), -- cần kiểm tra trùng CMND trong code, giới hạn nhập 9 số
	EMAIL VARCHAR(50), --cần kiểm tra trùng Email trong code, kiểm tra cú pháp email: xxx@gmail.com, xxx@yahoo.com
	SDT VARCHAR(20),	-- cần kiểm tra trùng SDT trong code, giới hạn nhập 11 số phải có số 0 đầu
	DIACHI NVARCHAR(200),
	TINHTRANG NVARCHAR(100), -- có 3 tình trạng "Đang hoạt động", "Ngưng hoạt động", "Đã bị xoá"
)


INSERT INTO NHANVIEN VALUES ('NV001','123',N'Nguyễn Quản Lý','1/10/1995','Nam','CV001','1/10/2016','0123456789','123@gmail.com','0912345678','78/7',N'Đang hoạt động')
INSERT INTO NHANVIEN VALUES ('NV002','123',N'Nguyễn Thủ Quỹ','1/10/1995','Nam','CV002','2/10/2016','0123456689','124@gmail.com','0912355678','78/7',N'Đang hoạt động')
INSERT INTO NHANVIEN VALUES ('NV003','123',N'Nguyễn Giám Sát','1/10/1995','Nam','CV003','3/10/2016','0123456669','125@gmail.com','0914445678','78/7',N'Đang hoạt động')

INSERT INTO NHANVIEN VALUES ('NV004','123',N'Lý Quốc Cường','1/10/1995','Nam',	'CV004','4/10/2016','0123456666','126@gmail.com','0912895678','78/7',N'Đang hoạt động')
INSERT INTO NHANVIEN VALUES ('NV005','123',N'Lê Văn Hoài','1/10/1995','Nam','CV004','5/10/2016','0123456755','127@gmail.com','0912349878','78/7',N'Đang hoạt động')
INSERT INTO NHANVIEN VALUES ('NV006','123',N'Nguyễn Tấn Đạt','1/10/1995','Nam','CV004','6/10/2016','0123456555','128@gmail.com','0912435678','78/7',N'Đang hoạt động')
INSERT INTO NHANVIEN VALUES ('NV007','123',N'Nguyễn Hoàng Hải','1/10/1995','Nam','CV004','7/10/2016','0123445489','129@gmail.com','0913345678','78/7',N'Đang hoạt động')


CREATE TABLE CALAM
(
	MACA VARCHAR(20),
	PRIMARY KEY(MACA),
	THOIGIAN NVARCHAR(100),
	SOTIENG INT, -- ăn gian chỗ này để dễ tính lương
)

INSERT INTO CALAM VALUES ('CA1','7:30 - 12:30',5)
INSERT INTO CALAM VALUES ('CA2','12:30 - 17:30',5)
INSERT INTO CALAM VALUES ('CA3','17:30 - 23:30',6)


CREATE TABLE LICHLAMVIEC -- bảng này chỉ xài cho nhân viên cùi bắp (part-time)
(
	MALLV VARCHAR(20),
	PRIMARY KEY(MALLV),

	MANV VARCHAR(20),
	FOREIGN KEY (MANV) REFERENCES NHANVIEN(MANV),

	NGAYLAMVIEC SMALLDATETIME,

	CONGVIEC NVARCHAR(50), 
	-- mình chỉ làm 3 công việc mặc định (bỏ trong combobox cho chọn): 'Bán vé', 'Xét vé', 'Trực phòng chiếu'
	
	MAPHONGCHIEU VARCHAR(20), 
	-- nếu là công việc "Trực phòng chiếu', 'Xét vé' thì phải chọn phòng chiếu nào, còn công việc khác thì bỏ trống

	MACA VARCHAR(20),
	FOREIGN KEY (MACA) REFERENCES CALAM(MACA),

	MANGS VARCHAR(20), --người tạo cái lịch này (Giám sát)
	FOREIGN KEY (MANGS) REFERENCES NHANVIEN(MANV),

	TINHTRANG NVARCHAR(100), -- có 4 tt: 'Đã làm', 'Chưa làm', 'Nghỉ việc' ,'Đã huỷ'
	/*
		'Chưa làm':khi mới tạo 1 LICHLAMVIEC mặc định sẽ là 'Chưa làm'.
		'Đã làm': Giám sát sẽ xác nhận nhân viên đó có đi làm, thì sẽ thay đổi trạng thái thành 'Đã làm'
		'Nghỉ việc': Giám sát sẽ xác nhận nếu nhân viên đó nghỉ buổi đó, thì sẽ thay đổi trạng thái thành 'Nghỉ việc'
		'Đã huỷ': khi Giám sát muốn huỷ 1 lịch làm việc

		Mình sẽ tính lương bằng tất cả ngày 'Đã làm' trong tháng của nhân viên đó, quy ra giờ rồi nhân với tiền.
	*/
)

INSERT INTO LICHLAMVIEC VALUES ('LLV001','NV004','10/10/2016',N'Bán vé',NULL,'CA1','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV002','NV005','10/10/2016',N'Xét vé','PC001','CA1','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV003','NV006','10/10/2016',N'Trực phòng chiếu','PC001','CA1','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV004','NV004','11/10/2016',N'Trực phòng chiếu','PC002','CA2','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV005','NV007','11/10/2016',N'Bán vé',NULL,'CA1','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV006','NV005','11/10/2016',N'Bán vé',NULL,'CA3','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV007','NV006','11/10/2016',N'Xét vé','PC002','CA2','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV008','NV007','12/10/2016',N'Bán vé',NULL,'CA1','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV009','NV007','12/10/2016',N'Trực phòng chiếu','PC003','CA3','NV003',N'Chưa làm')
INSERT INTO LICHLAMVIEC VALUES ('LLV010','NV004','12/10/2016',N'Xét vé','PC003','CA3','NV003',N'Chưa làm')


CREATE TABLE LOAIKH
(
	MALOAI VARCHAR(20),
	PRIMARY KEY(MALOAI),

	DIEM INT,
	/*
		Điểm này là điểm tích luỹ trong năm
		Quy tắc tính điểm - nâng cấp khách hàng:

			+	Khi cộng điểm vào DIEMTICHLUY trong KHACHHANG (xảy ra khi khách hàng mua vé xem phim, lúc 
			đó sẽ có HOADON và cộng điểm), ta sẽ tính xem trong năm hiện tại, 
			tổng số tiền (điểm) mà khách hàng này chi là bao nhiêu (thông qua HOADON). 
				Nếu >=3,5 củ và là MEMBER thì tăng làm VIP.
				Nếu >=8,8 củ và là VIP thì tăng làm V-VIP.

			+	Vào 1/1 hằng năm hệ thống sẽ xem xét giảm cấp khách hàng. Ví dụ vào 1/1/2017, sẽ tính
			tất cả hoá đơn trong năm 2016, xem mỗi khách hàng chi tất cả bao nhiêu tiền trong năm 2016. 
				Nếu < 3,5 củ và là cấp VIP thì giảm thành MEMBER
				Nếu < 8,8 củ và là cấp V-VIP thì giảm thành VIP
	*/
)

INSERT INTO LOAIKH VALUES ('MEMBER',0)
INSERT INTO LOAIKH VALUES ('VIP',3500000)
INSERT INTO LOAIKH VALUES ('V-VIP',8800000)-- Siêu VIP


CREATE TABLE KHACHHANG
(
	MAKH VARCHAR(20),
	PRIMARY KEY(MAKH),
	MALOAI VARCHAR(20),
	FOREIGN KEY(MALOAI) REFERENCES LOAIKH(MALOAI),
	DIEMTICHLUY INT, -- số điểm = số tiền mua vé 

	HOTEN NVARCHAR(100),
	NGAYSINH SMALLDATETIME,
	NGAYDK SMALLDATETIME, --Ngày đăng kí (Today)
	CMND VARCHAR(20),
	SDT VARCHAR(20),
	DIACHI NVARCHAR(20),
)


INSERT INTO KHACHHANG VALUES ('KH001','MEMBER',0,N'Phạm Thi Vương','1/1/1980','1/10/2013','099123456','0982211111','55/15')
INSERT INTO KHACHHANG VALUES ('KH002','MEMBER',0,N'Phan Nguyệt Minh','1/1/1980','1/10/2013','099123456','0982211111','55/15')
INSERT INTO KHACHHANG VALUES ('KH003','MEMBER',0,N'Dương Tôn Đảm','1/1/1980','1/10/2013','099123456','0982211111','55/15')
INSERT INTO KHACHHANG VALUES ('KH004','MEMBER',0,N'Nguyễn Tuấn Anh','1/1/1980','1/10/2013','099123456','0982211111','55/15')
INSERT INTO KHACHHANG VALUES ('KH005','MEMBER',0,N'Trần Anh Dũng','1/1/1980','1/10/2013','099123456','0982211111','55/15')


CREATE TABLE HOADON
(
	MAHD VARCHAR(20),
	PRIMARY KEY(MAHD),

	MANV VARCHAR(20), --NGUOI BÁN
	FOREIGN KEY (MANV) REFERENCES NHANVIEN(MANV),

	MAKH VARCHAR(20),
	FOREIGN KEY (MAKH) REFERENCES KHACHHANG(MAKH),

	NGAYBAN SMALLDATETIME,
	GIAVE INT, ---lấy giá trị bên bảng THAMSO điền vào tự động, ko được nhập vào.
	SOLUONG INT,
	GIATIEN INT,
)


CREATE TABLE CT_HOADON -- MỘT HOÁ ĐƠN CÓ THỂ MUA NHIỀU VÉ
(
	MAHD VARCHAR(20),
	FOREIGN KEY(MAHD) REFERENCES HOADON(MAHD),

	MAVE VARCHAR(20),
	FOREIGN KEY (MAVE) REFERENCES VE(MAVE),

	PRIMARY KEY(MAHD,MAVE),
)


CREATE TABLE BANGLUONG 
(
	MABANGLUONG VARCHAR(20),
	PRIMARY KEY(MABANGLUONG),

	THANG INT,
	NAM INT,
	TONG DECIMAL,
)

/*
	Phân biệt nhân viên:
		Nếu MANV = 'CV004' thì là part - time
		còn lại là làm full-time
*/


CREATE TABLE CT_BANGLUONG	
(
	MABANGLUONG VARCHAR(20),
	FOREIGN KEY(MABANGLUONG) REFERENCES BANGLUONG(MABANGLUONG),

	MANV VARCHAR(20),
	FOREIGN KEY(MANV) REFERENCES NHANVIEN(MANV),
	PRIMARY KEY(MABANGLUONG,MANV),

	MATHUQUY VARCHAR(20),--người sẽ phát lương cho nhân viên

	TONGTIME INT, -- tổng số thời gian làm việc trong tháng (part-time), nếu full-time thì NULL
	HESOLUONG INT, -- lương 20k/giờ lấy trong bảng CHUCVU (part-time), nếu full-time thì NULL
	TONGTIEN INT, -- = TONGTIME * HESOLUONG (part-time) ;
				 -- = LUONG trong table CHUCVU (full-time);
	TINHTRANG NVARCHAR(100), --có 2 tình trạng: 'Chưa phát', 'Đã phát'
	/*
		Nếu từ 'Chưa phát' chuyển sang 'Đã phát' thì phải trừ vào TIENVON trong bàng THAMSO
	*/
)


CREATE TABLE THAMSO
(
	TIENVON DECIMAL, ---số tiền vồn hiện tại của rạp phim, mỗi lần bán được 1 vé thì phải cộng thêm tiền vào
	GIAVE INT,
)

INSERT INTO THAMSO VALUES (100000000,90000)
