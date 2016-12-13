#include "DB.hpp"
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <string>

int prob[] = {310,521,642,709,771,803,833,862,890,913,934,955,976,997,1017,1037,1056,1075,1093,1109,1124,1137,1150,1162,1174,1185,1195,1204,1212,1219,1226,1232,1238,1243,1248,1253,1258,1263,1268,1273,1278,1283,1288,1293,1298,1302,1306,1310,1314,1318};

// 출현 빈도 높은 순으로 정렬 (50개 성씨) - 추가하면 안됨.
char	Last[] = "\0김\0이\0박\0최\0정\0강\0조\0윤\0장\0임\0오\0한\0신\0서\0권\0황\0안\0송\0류\0홍\0전\0고\0문\0손\0양\0배\0조\0백\0허\0남\0심\0유\0노\0하\0전\0정\0곽\0성\0차\0유\0구\0우\0주\0임\0나\0신\0민\0진\0지\0엄";

// 이름 (무작위) - 수정 가능
char	First[] = "\0가현\0가혜\0가희\0강석\0강윤\0강은\0강준\0강현\0강혜\0건석\0건수\0건우\0건의\0건태\0건호\0건희\0경구\0경문\0경미\0경민\0민성\0영지\0재희\0경선\0경수\0경아\0경애\0경윤\0경주\0경진\0경철\0경헌\0경혜\0경호\0경화\0동욱\0동우\0동해\0동희\0경후\0윤하\0성목\0경희\0관우\0광수\0광철\0구철\0규리\0규림\0규보\0규민\0규석\0규식\0규연\0규태\0규헌\0구헌\0규혁\0규현\0규화\0규환\0규희\0그린\0그림\0근수\0기덕\0기민\0기쁨\0기석\0기철\0기훈\0길수\0나나\0나래\0나림\0나연\0나정\0나현\0남주\0남혁\0노아\0노을\0누리\0늘찬\0다솜\0다연\0다영\0다은\0다현\0다혜\0단비\0달빛\0달수\0담비\0대경\0대영\0대종\0대준\0대중\0대한\0대훈\0덕수\0도담\0도열\0도윤\0도현\0도희\0동엽\0동인\0동춘\0동탁\0동현\0두기\0두환\0라연\0라영\0라예\0라임\0라희\0로운\0루나\0루미\0리나\0리내\0마루\0마리\0만세\0명박\0명선\0명섭\0명호\0명희\0무현\0문도\0문량\0문별\0문성\0문주\0문호\0문희\0미경\0미란\0미령\0미라\0미르\0미리\0미선\0정선\0은현\0미애\0미연\0미영\0미정\0미주\0미진\0상영\0미향\0미현\0미혜\0미화\0미희\0민경\0민진\0민국\0민규\0민균\0민상\0민서\0민석\0민수\0민아\0민영\0민욱\0민율\0민재\0민정\0민종\0민주\0민준\0민지\0민철\0민하\0민혜\0민호\0민희\0바다\0바람\0백기\0백수\0백천\0범규\0범석\0범재\0별빛\0별찬\0병대\0병수\0병욱\0병인\0보검\0보겸\0보규\0보담\0보람\0보리\0보미\0보민\0보석\0보영\0보정\0보희\0봄빛\0빛나\0사랑\0강산\0산새\0상민\0상수\0상은\0상재\0상주\0상철\0상태\0상호\0상훈\0새벽\0새봄\0샛별\0서연\0서영\0서준\0서윤\0서현\0석주\0석준\0석희\0선규\0선미\0선아\0선엽\0선영\0선오\0선용\0선우\0선재\0선주\0선호\0선화\0선희\0설아\0설주\0설현\0설혜\0설희\0희섭\0성규\0성기\0성길\0성모\0성민\0성미\0성보\0성새\0성소\0성수\0성열\0성오\0성욱\0성웅\0성윤\0성은\0성종\0성주\0성준\0성진\0성혁\0성현\0성혜\0성호\0성훈\0성희\0세리\0세라\0세영\0세윤\0세정\0세종\0세준\0세진\0세찬\0세한\0세현\0세호\0세훈\0소라\0소미\0소아\0가람\0소연\0소영\0소유\0소윤\0소율\0소은\0소진\0소현\0솔길\0솔잎\0솔희\0송희\0수경\0수미\0수민\0수빈\0수아\0수애\0수연\0수완\0수인\0수정\0수지\0수진\0수찬\0수철\0수혁\0수현\0수혜\0수호\0수희\0숙자\0숙희\0순신\0순영\0순옥\0순자\0순철\0순호\0숭겸\0슬기\0슬비\0슬아\0슬현\0승혜\0지숙\0승헌\0승관\0승권\0승기\0승리\0승만\0승민\0승범\0승아\0승연\0승우\0승일\0승지\0승탁\0승혁\0승현\0승호\0승희\0시현\0시후\0시내\0시라\0시원\0시윤\0시정\0시진\0신애\0신영\0신욱\0신호\0신희\0아담\0아라\0아란\0아람\0아름\0아리\0아벨\0아솔\0아솜\0아영\0아현\0안수\0안영\0애란\0엄지\0여름\0여옥\0여진\0연경\0연성\0연아\0연우\0연이\0연주\0연지\0애지\0연희\0영길\0영록\0영롱\0영리\0영만\0영미\0영민\0영삼\0영석\0영수\0영숙\0영식\0영실\0영아\0영우\0영웅\0영일\0영재\0영주\0영준\0영진\0영찬\0영철\0영호\0영환\0영희\0예리\0예영\0예원\0예준\0남석\0예지\0예진\0예찬\0예희\0오성\0옥순\0옥자\0완섭\0요환\0용상\0용석\0용성\0용수\0용익\0용인\0우주\0우석\0우진\0원경\0원준\0월영\0월예\0위림\0유경\0유나\0유라\0유람\0유리\0유린\0유미\0유민\0유비\0유빈\0유선\0유성\0유정\0유진\0유화\0유희\0윤도\0윤서\0윤설\0윤성\0윤아\0윤옥\0윤일\0윤재\0윤정\0윤주\0윤진\0윤찬\0윤태\0윤형\0윤호\0율성\0으뜸\0은경\0은규\0은미\0은민\0은비\0은설\0은수\0은숙\0은슬\0은아\0은영\0은주\0은준\0은지\0은진\0은혜\0의섭\0의정\0의찬\0의철\0이린\0이슬\0이안\0이지\0익현\0인건\0인수\0인영\0인철\0인화\0인희\0일권\0일성\0잎새\0자철\0자춘\0자현\0잔디\0장비\0재규\0재민\0재범\0재석\0재선\0재섭\0재성\0재연\0재윤\0재율\0재은\0재인\0재찬\0전희\0정남\0정미\0정민\0정복\0정석\0정수\0정숙\0정순\0정식\0정심\0정아\0정연\0정옥\0정운\0정웅\0정은\0정자\0정재\0정종\0정준\0정진\0정철\0정태\0정하\0정한\0정헌\0정혁\0정헌\0정현\0정호\0정훈\0정흠\0정희\0제성\0제원\0조은\0종덕\0종석\0종성\0종수\0종철\0종혁\0종현\0종호\0종흠\0주경\0주래\0주리\0주린\0주만\0주명\0주미\0주상\0주성\0주석\0주선\0주안\0주연\0주엽\0주용\0주원\0주재\0주찬\0주철\0주혁\0주현\0주호\0주희\0준모\0준서\0준석\0준수\0준오\0준철\0준탁\0준태\0준학\0준혁\0준현\0준호\0준후\0준휘\0중수\0지개\0지담\0지만\0지민\0지선\0지수\0지아\0지애\0지연\0지영\0지용\0지우\0지원\0지윤\0지은\0지철\0지헌\0지혁\0지현\0지혜\0지예\0지호\0지후\0지훈\0지희\0진구\0진규\0진미\0진배\0진서\0진섭\0진성\0진수\0진아\0진영\0진우\0진욱\0진일\0진주\0진태\0진헌\0진혁\0진현\0진형\0진호\0진후\0진희\0찬숙\0찬우\0찬주\0찬호\0찬휘\0찬희\0창원\0창재\0채리\0채민\0채아\0채영\0천희\0철규\0철기\0철민\0철수\0철영\0철훈\0초롱\0춘삼\0춘자\0춘화\0충성\0충희\0치훈\0탐희\0태겸\0태민\0태성\0태식\0태연\0태오\0태우\0태일\0태종\0태진\0태평\0상아\0태현\0태형\0태훈\0태희\0택수\0판규\0하나\0하늘\0하늬\0하니\0하라\0하람\0하랑\0하루\0하리\0하민\0하신\0하얀\0하연\0하영\0하율\0하은\0하정\0하준\0하진\0한나\0한별\0한빛\0한울\0해련\0해성\0해윤\0해인\0혁수\0혁재\0현오\0현미\0현민\0현선\0현성\0현숙\0현아\0현우\0현재\0현정\0현주\0현지\0현진\0현철\0현희\0형미\0형석\0형우\0형주\0형준\0형진\0형철\0혜라\0혜령\0혜리\0혜림\0혜미\0혜민\0혜선\0혜수\0혜슬\0혜승\0예슬\0혜승\0혜연\0혜영\0혜원\0혜은\0혜인\0혜정\0혜주\0혜지\0혜진\0호람\0호석\0호섭\0호성\0호준\0호철\0홍도\0홍빈\0홍익\0화경\0환종\0환주\0환준\0회창\0효민\0효식\0효신\0효연\0효영\0효정\0훈규\0휘재\0희경\0희덕\0희도\0희라\0희민\0희선\0희성\0희수\0희순\0희연\0희열\0희영\0희윤\0희주\0희준\0희진\0희창\0희향\0소희";

DB::DB()
{
  numOfStudent = 0;
}

DB::~DB()
{
  /*
  for(int i = 0 ; i < numOfStudent; i++)
    AllStudent[i].~Student();
   */
}

void DB::InitDB(int numberOfStudents)
{
  srand(unsigned(time(NULL)));
#ifdef TEST
  puts("랜덤 시드 생성");
#endif
  for(int i = 0 ; i < numberOfStudents ; i++)
  {
    CreateRandomStudent(AllStudent[i]);
#ifdef TEST
    printf("%d 번째 학생이 생성되었습니다.\n", i+1);
#endif
  }
  numOfStudent = numberOfStudents;
}

void DB::CreateRandomStudent(Student &A) // 학생 A의 정보를 랜덤하게 생성한다.
{
  // unsigned int ID;      // 학번
  // std::string name;     // 이름
  // Subject* subarr;      // 수강한 과목들
  // unsigned int subcnt;  // 수강한 과목 수
  // unsigned int sumsisu; // 수강한 과목 시수 총합 (수강한 학점)
  // double GPA;           // GPA
  
  /* Create random ID */
  // 중복 체크를 하지 않음!!!!
                          // 2007 ~ 2016 입학년도
                          // 31 학부
                          // 0236 (0000~9999)
  A.ID = 2000;
  int year = rand() % 10 + 7;
  A.ID += year;
  A.ID *= 100; A.ID += 31;
  A.ID *= 10000;
  A.ID += rand() % 9999 + 1;
  
  // Create random name
  int tt = rand() % 1318;
  tt = int(std::upper_bound(prob, prob+50, tt) - prob);
  int tt2 = rand() % ((sizeof(First))-1)+1;
  char *last_name = Last + 1 + tt * 4;
  while(*--last_name != '\0');
  last_name++;
  char *first_name = First + tt2;
  while(*--first_name != '\0');
  first_name++;
  A.name = std::string(last_name) + std::string(first_name);

#ifdef TEST
  puts("이름 생성이 끝났습니다.");
#endif
  // Create random subcnt (0~50) // 수강 과목 수
  int cnt = rand() % 50;
  
  A.subcnt = 0;
  // 수강한 모든 과목
  
  // Create random subject        // 들을 교양 과목이 남아있음
  while( A.general != ((1u<<GENERALSIZE)-1) && A.subcnt < cnt && A.sumsisu < 35) // 수강한 교양 학점이 35 학점 이하이면
  {
    A.addRandomGeneralSubject();
    A.subcnt++;         // 과목 수 증가
   
  }
#ifdef TEST
  puts("교양 과목 생성이 끝났습니다.");
#endif
  // 16학번은 전공 x
  while(A.major != ((1ULL<<CSESIZE)-1) && year < 16 && A.subcnt < cnt && A.sumsisu < 140) // 나머지는 졸업할 때까지 전공으로 채움
  {
#ifdef TEST
    printf("%llx %llx %d %d %d %d\n", A.major, (1ULL<<CSESIZE)-1, year, A.subcnt, cnt, A.sumsisu);
#endif
    A.addRandomCSESubject(); // 랜덤하게 생성
    A.subcnt++;
  }
#ifdef TEST
  puts("전공 과목 생성이 끝났습니다.");
#endif
  // Create random sum sisu (subject를 만들면서 자동 생성)

  // Create random GPA (subject를 만들면서 자동 생성)
  
  // Create random year (sum sisu를 만들면서 자동 생성) (~35, ~70, ~105, ~140)
  tt = A.sumsisu / 35;
  if( tt > 4 ) tt = 4;
  A.SetYear(tt+1);
}

void DB::AddStudent(std::string name)
{
  AllStudent[numOfStudent] = Student(name);
  
#ifdef TEST
    printf("%d 번째 학생이 생성되었습니다.\n", numOfStudent);
#endif
}

void DB::SearchDB(unsigned int ID)              // ID로 검색
{
  for(int i = 0 ; i < numOfStudent ; i++)
  {
    if(AllStudent[i].ID == ID)
    {
      AllStudent[i].PrintDetail();
      break;
    }
  }
}


void DB::PrintDB() // 전체 DB를 출력한다.
{
  puts("DB 전체 정보를 출력합니다.");
  puts("");
  puts("==================================================");
  puts("학번        이름      학년   수강과목 수  수강 학점    GPA");
 //     2014311221 이훈규      1         16       33    3.52
  for(int i = 0 ; i < numOfStudent ; i++)
  {
    this->AllStudent[i].Print();
  }
  puts("==================================================");
}