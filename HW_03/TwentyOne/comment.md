# Casino

### Class Guest

#### Constructor & Destructor
* *Guest();* 空
* *Guest(string s, int m, int ski);* 設定 Private 變數
* *~Guest();* 空

#### method
* *string get_name();* get private attribute: name
* *int get_money();* get private attribute: money
* *int get_skill();* get private attribute: skill
* *void Win(int m);* 對該客人加上賺來的錢

#### Attributes
* *string name;* 客人的名字
* *int money;* 客人的錢；會扣掉入場費或加上贏的錢
* *int skill;* 客人的贏錢上限

### Class Casino

#### Constructor & Destructor
* *Casino();* 初始化入場費、總收入、兩名單的數量
* *~Casino();* 空

#### method
* *void Enterance(int f);* 設定入場費
* *void GuestEnter(string s, int m, int ski);*
    * 檢查是否已存在，是則 return
    * 檢查是否在黑名單，是則 return
    * 是否付得起入場費
        * 是：收入場費後 new 一個客人並存到 list 裡面
        * 否：收現有的前後咧入黑名單
* *void Win(string s, int m);*
    * 檢查是否已存在，否則 return
    * 檢查是否在黑名單，是則 return
    * 是否有作弊
        * 是：錢給他之後列入黑名單
        * 否：呼叫 Guest Class 的 Win(money) 更新該客人的錢，並檢查是否輸到破產
            * 是：只拿他現有的錢，更新總收入，並列入黑名單
            * 否：更新總收入
* *void EndDay();* 客人數設為 0
* *void Result();* 輸出 OuO

#### Attributes
*int fee;* 當日入場費，每天更新

*int guest_num;* 客人人數，Queue 的 rear
*Guest *guest[1009];* 陣列裡裝著指向 Guest 物件的指標

*int income;* 總收入
*int list_num;* 黑名單人數，Queue 的 rear
*string blacklist[1009];* 黑名單的名字