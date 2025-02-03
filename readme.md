# Temporizador de Disparo Único (One Shot) - Controle de LEDs com Botão

Este projeto implementa um sistema de temporização para acionar LEDs (azul, verde e vermelho) com o clique de um botão (pushbutton), utilizando a função `add_alarm_in_ms()` do Pico SDK. O sistema controla o acionamento dos LEDs com um atraso de 3 segundos entre os estados de acionamento.

## Requisitos

### Hardware Necessário:
- **Microcontrolador Raspberry Pi Pico W**
- **3 LEDs**: Azul, Vermelho e Verde
- **3 Resistores de 220 Ω**
- **1 Botão (Pushbutton)**

### Comportamento do Sistema:
1. **Ação Inicial (Botão Pressionado)**:
   - Quando o botão é pressionado, todos os LEDs são acesos simultaneamente.
   - Após 3 segundos, dois LEDs são desligados, e após mais 3 segundos, apenas um LED permanece aceso.
   - O botão só pode iniciar a sequência de LEDs quando todos os LEDs estiverem apagados.

2. **Temporização**:
   - O temporizador é configurado para disparar a cada 3 segundos, alternando os LEDs entre diferentes estados de acionamento.
   - O estado dos LEDs muda da seguinte forma:
     - Todos os LEDs acesos → Dois LEDs acesos → Um LED aceso → Todos os LEDs apagados.


## Diagrama de Conexão

- **LED Verde**: Conectado ao pino GPIO 11.
- **LED Azul**: Conectado ao pino GPIO 12.
- **LED Vermelho**: Conectado ao pino GPIO 13.
- **Botão (Pushbutton)**: Conectado ao pino GPIO 5 com resistor de pull-up.

## Como Funciona

1. **Pressionando o Botão**:
   - Ao pressionar o botão, todos os LEDs são acesos ao mesmo tempo.
   
2. **Mudança de Estado**:
   - **Após 3 segundos**: Dois LEDs serão desligados, mantendo um aceso.
   - **Após mais 3 segundos**: Apenas um LED permanece aceso e os outros são desligados.
   
3. **Prevenção de Pressionamento Repetido**:
   - O sistema bloqueia a entrada do botão durante a execução da sequência, permitindo que o próximo ciclo só seja iniciado quando todos os LEDs estiverem apagados.

## Como Executar

### 1. **Configuração do Hardware**:
   - Conecte os LEDs aos pinos GPIO 11, 12 e 13, utilizando resistores de 220 Ω em série.
   - Conecte o botão ao pino GPIO 5 com resistor de pull-up interno ativado.

### 2. **Compilação e Upload do Código**:
   - Compile o código utilizando o Pico SDK.
   - Faça o upload do código para o microcontrolador Raspberry Pi Pico.


## Considerações
  
- **Expansão do Projeto**: O sistema pode ser facilmente adaptado para controlar mais LEDs ou alterar os tempos de acionamento dos LEDs.

## Referências

- [Pico SDK Documentation](https://www.raspberrypi.org/documentation/pico/getting-started/)
- [Pico Time API](https://raspberrypi.github.io/pico-sdk-doxygen/group__time.html)
