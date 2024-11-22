# ConsoleGameLinux
Console game for linux

## 🧑🏻‍💻 팀 소개

<div align="center">

|                                                            **이경민**                                                             |                                                               **박수민**                                                                |                                                                 **서지형**                                                                  |                                                              **지아넬라**                                                               |
| :----------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------: |
| [<img src="https://avatars.githubusercontent.com/u/171900443?v=4" height=150 width=150> <br/> @pinkbuger](https://github.com/pinkburger) | [<img src="https://avatars.githubusercontent.com/u/65269430?v=4" height=150 width=150> <br/> @Moderator11](https://github.com/Moderator11) | [<img src="https://avatars.githubusercontent.com/u/169060773?v=4" height=150 width=150> <br/> @jise-2](https://github.com/jise-2) | [<img src="https://avatars.githubusercontent.com/u/150573808?v=4" height=150 width=150> <br/> @cinmon](https://github.com/cinmon) |

</div>

## 🔧 개발 환경

-   개발 도구 및 언어 : Visual Studio Code, C [gcc (Debian 12.2.0-14) 12.2.0]

-   사용된 외부 라이브러리 : Curses [Terminal control library]

-   서비스 배포 환경 : Linux

-   버전 및 이슈관리 : Github

<br>

## ✏️ 기술스택
<div style="display: flex;">
  <img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white">
  <img src="https://img.shields.io/badge/Github-181717?style=for-the-badge&logo=github&logoColor=white">
  <img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=white">
</div>
<!--https://cocoon1787.tistory.com/689-->
<br>

## ⚙️ 개발 주안점

### [Game Engine]

-   키보드 IO 시그널을 통해 사용자의 입력을 처리합니다
-   SIGINT, SIGQUIT 시그널을 블록해 의도치 않은 종료를 방지합니다
  
### [Physic Engine]

-   강체 물리를 시뮬레이션 합니다.
-   iTimer를 이용해 프레임마다 물리 연산을 처리합니다
-   물체와 경계 사이의 충돌을 감지하고 처리합니다.

<br>
