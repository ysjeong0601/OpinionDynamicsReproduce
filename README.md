# OpinionDynamicsReproduce
Opinion dynamics model reproduce

모든 dynamic 모델들은 클래스로 만들었습니다.  
기본적으로 모델을 사용하기 위해서는 네트워크의 정보를 담고 있는 network 객체를 필요로 합니다.

* ## Network 클래스의 객체 생성

  기본적으로 랜덤네트워크를 구성합니다.  
  * ### 노드 개수와 링크 개수로 구성하기

    ```cpp
    Network network(false,100,20);
    ```
    인자 순서대로 의미하는 값들은 weight여부, 노드 개수, 링크 개수  
    
    
  * ### 노드 개수와 노드 간 연결 확률로 구성하기
    ```cpp
    Network network(false,100,20);
    ```
    
  * ### 바라바시-알버트 모델
    바라바시 알버트 모델을 이용해 Scale-free 네트워크를 만들려면 다음 함수를 이용하면 됩니다.
    ```cpp
    Network network;
    network.generate_Barabasi_Albert(100000);
    ```
    해당 코드의 경우 초기 노드의 숫자가 3이며 새로운 노드 생성시 2개의 링크를 갖도록 작성되어 있습니다.  
    인자로는 원하는 시스템 크기입니다.
  
  
* ## Dynamic 클래스의 객체 생성

  원하는 다이나믹 모델의 객체 생성을 합니다. 구현한 모델들은 다음과 같습니다.  
  - Voter model
  - Majority model
  - Sznajd model
  - Deffuant model
  - Hegselmann-Krause model

  객체 생성은 다음과 같습니다.
    ```cpp
    Voter voter("voter_output");
    voter.setNetwork(network);
    ```
    또는
    ```cpp
    Voter voter(network,"voter_output");
    ```
    인자로는 결과를 출력할 "파일명"이 반드시 필요합니다. network객체를 객체 생성시 추가하지 않았다면 반드시 setNetwork를 통해 네트워크를 받아야 합니다.
    
  voter model의 경우 초기값으로 두 의견 A,B의 비율을 가지며 객체 생성시 기본값으로 0.5,0.5 설정됩니다.
  setFraction_A 함수를 이용해 두 의견의 비율을 설정할 수 있습니다.
  ```cpp
  voter.setFranction_A(0.6);
  ```
  모든 설정이 끝나면 run(시간) 함수를 이용해 결과를 볼 수 있습니다.
  ```cpp
  voter.run(1000);
  ```
  결과는 시간, 의견A 비율, 의견B 비율, 전체 의견 평균으로 출력됩니다.
  
  </br></br>
* 주의사항
  - Deffuant , Hegselmann-Krause 모델들의 경우 매 시간마다 모든 노드들의 의견 상태를 저장하기 때문에 노드수가 많아지면 출력되는 데이터가 많아져 파일의 크기가 매우 커집니다. 따라서 해당 모델들의 결과를 확인하려면 가능한 작은 네트워크를 이용해 주세요.
  - 각 모델들은 정의에 따라 필요한 파라미터들이 있습니다. 그러므로 run 하기 이전에 반드시 다이나믹스 모델 객체에 파라미터들을 설정해야 바르게 작동됩니다.
  
    
</br></br></br>
다이나믹스 모델들은 Castellano, C., Fortunato, S. & Loreto, V. Statistical physics of social dynamics. _Rev. Mod. Phys_. 81, 591–646 (2009) 논문을 참고하여 작성되었습니다.
