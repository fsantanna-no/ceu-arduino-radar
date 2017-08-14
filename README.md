# ceu-arduino-radar

- medir frequencias do movimento e toque
- medir corrente gasta nos dois projetos
- calcular tempo de ping para medir a velocidade mais certinho
    - NRF e Bluetooth 2 e 4

- 120us: tempo de medida do analogRead
- 200us: tempo seguro para ler o mais rapido que conseguir
- 512 medidas, cada uma a 200us: 200us*512=524288us = 520ms de jogo

- TODO
    - comprar
        - cabos miltimetro
        - resistor 22k (mic), 30/40k (bat)
        - TP4056 (com proteção?)
        - baterias pequenas
        - microfones
        - fio removedor de solda
        - esponja solda
        - 4 radios
        - 4 pro-mini
        - Video + Som
            - Cabo RCA -> P3
            - P3 jack
        - Bluetooth 3.3V
            - v4 ou v2?


- TODO:
    - testar delay do RF
        - com 1, 2, 4, 8, 16 bytes transmitidos
    - apito pra dizer que pode comecar
    - apito pra dizer que caiu
    - tempo de pausa
        - pode somar 1 minuto
            - depois comeca a contar quedas

- media dos 40+15 ataques mais potentes de fore/back
- contar ataque/defesa/toque, voltar o tempo na queda

- comprar
    - case
    - conectores
        - linha femea/femea
        - multimetro agarra
    - talvez
        - microfone MEMS

- make ARD_BOARD=nano:cpu=atmega328 ARD_PORT=/dev/ttyUSB0 CEU_SRC=ceu-arduino-radar/client/main.ceu
- make ARD_BOARD=pro:cpu=8MHzatmega328 ARD_PORT=/dev/ttyUSB0 CEU_SRC=ceu-arduino-radar/client/main.ceu

- stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
- cu -l /dev/ttyACM0
    - ~.

- NOTA
    V = velocidade
        Avalia a velocidade média do jogo.
        - conta todas as bolas
        - total de toques / tempo total
        - NOTA TÍPICA?
            - [0 -> _[
    P = potência
        Avalia a potência média dos ataques mais velozes.
        Avalia a potência dos dois lados.
        - conta um máximo Px de bolas
        - soma dos Px toques de maior velocidade / Px
            - para cada atleta P1 e P2
        - P = (P1 + P2) / 2
        - um jogo de 5 minutos tem de 300 a 600 toques
            - se há um ataque a cada dois toques
                - 150 a 300 ataques
            - são dois jogadores
                - 75 a 150 ataques por jogador
            - fazendo uma média puxando um pouco pra baixo
                - Px = 100
        - dos 100 quantos de revés?
            - Py = 15
        - NOTA TÍPICA?
            - [0 -> _[
    E = equilíbrio
        Avalia o equilíbrio na imposição do ritmo do jogo.
        - conta um máximo Ex de bolas
            - para simplificação Ex=Px
        - E = (1 - min(P1,P2)/max(P1,P2)) * 100
        - NOTA TÍPICA?
            - [0 -> 100]
        - E1: equilibrio de velocidade
            - cada sequencia
            - leva em consideracao apenas quem esta atacando (batendo mais forte)
                - um ataque = 1 ponto
            - diferenca de pontos é determinante na nota de equilibrio
                - somatorio(m/M * toques) / toques*100
            - NOTA TÍPICA?
                - [0 -> 100]
        - E2: equilibrio de potencia
            - jogo inteiro
        - Chamar de Ve e Pe
    S = sequências
        Avalia as quedas de bolas.
        - S = 
        - NOTA TÍPICA?
            - ]0 -> 100]

    - Se o jogo A foi igual ao jogo B, mas teve algum detalhezinho melhor, em
      qualquer critério, a nota de A deve obrigatoriamente ser maior que a de B.
        - Por isso não há nota máxima para V e P, sempre há o que melhorar.

    - No final, vamos pegar um jogo "perfeito" em cada critério e colocá-lo com
        V = P = E = S = 100
        - esses são os 100 a serem batidos em cada um dos critérios
    - Cada campeonato pode favorecer um critério com fatores
        - ainda assim, a soma "perfeita" deve ser 400
        - ex
            - V * 0.8
            - P * 1.2
            - E * 0.8
            - S * 1.2
                - esse jogo favorece potência e sequências
                    - Provavelmente a melhor estratégia é
                        - uma defesa mais lenta e segura que permita ataques
                          potentes com poucas quedas
                        - um desequilíbrio em favor do jogador que ataca mais forte
                    
