Xét chương trình chạy không như ý như sau:
Như ta thấy chương trình chỉ nhận là xử lý gói tin đầu tiên, các gói tin sau tuy vẫn được nhận nhưng ko được xử lý và in ra

Lý do như sau
Xét từ lúc ESP mới được cấp nguồn(hoặc ngya sau khi được reset), đoạn này có chức năng kiểm tra có dử liệu bên ngoài (cụ thể ở đây là các modbus slave),  nếu có thì having_respo = 1 ngược lại thì bằng không, lưu ý trong này có hàm .available() trả về số byte của gói tin.
Gí sử có 1 gói dữ liệu đầu tiên được gửi tới kể từ ngay sau khi được cấp nguồn hoặc RESET, availabe() lúc này > 0,  having_response = 1
tiếp tục các dòng lệnh dưới, nếu having_response == 1 thì gói tin được xử lý bằng hàm parsePacket(), theo cách mà thư viện ESP tổ chức thì các gói tin được tổ chuwscc dưới dạng danh sách liên kết, vì gói vừa nhận được là gói đàu tiên và theo sourrce code thì, if (!_first_buf_taken) nghĩa là nếu gói đầu tiên chưa được tử xử thì dang sách liên kết vẫn trỏ ngay tại gói tin đầu tiên,  còn nếu là gói tin ko phỉa gói tin đầu tiên thì danh sách liên kết sẽ trỏ tới gói tin tiếp theo của danh sách băng đoạn code _rx_buf->next;

từ đây ta suy luận được rằng, vì là gói tin đầu nên sau khi parsePacket thì sẽ ko trỏ tơi vùng nhớ của gói tin tiếp theo, mà sau khi parsePacket thì hàm .available() sẽ trả về 0 vì dữ liệu của gói đã được đọc hết trong hàm parsePacket

trong vòng lặp tiếp theo của chương trình
nếu có gói tin nào tới thì available vẫn trả về 0 do danh sách liên kết ko trỏ tới vùng nhớ của gói tin tiếp theo, vì vậy đonạ code 
  if(having_response)
  {
    master.parsePacket();
    Serial.print("Get from: ");
    Serial.println(master.remoteIP().toString());

    register_t temp_reg[10];
    master.RTUUDPGetReadHoldingRegistersValue(temp_reg);
    for(uint8_t j = 0; j < 10; j++)
    {
      Serial.println(temp_reg[j]);
    }
  }

  sẽ ko đc thực thi do having_response == 0 (do available() trả về 0)
  do đó mà các gói tiếp theo sẽ ko được parsePacket()

  Để khắc phục ta làm như sau

  vì sau làm vậy, vì sau khi parsePacket gói tin đầu tiên thì _first_buf_taken sẽ được check, vì vậy master.parsePacket() sẽ trả về getSize và số này sẽ khác 0 (vì có dữ liệu từ gói tin), khi đó điều kiện trong while sẽ khác 0, vì vậy sẽ có lần parsePacket thứ 2 xảy ra dù ko có gói dữ liệu thứ 2, lúc này nếu có gói tin thứ 2 thì gói 1 sẽ đc giải phóng do đó available sẽ trả về số byte dữ liệu của gói 2, và nếu gói thứ 2 được gửi về ESP thì nó sẽ được phân tích vì available lúc này là thực hiện cho gói thứ 2, mà gói thứ 2 vẫn chưa được parsePacket nên available sẽ trả về 1 số > 0

  OK