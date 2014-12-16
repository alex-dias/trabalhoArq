<h2>Grayscale Filter</h2></br>
<hr>
<h4>O filtro</h4>

O filtro Grayscale tem como objetivo transformar uma imagem colorida em uma imagem acinzentada utilizando escalas de cinza. Isso é feito através de um sistemas de peso, atribuindo um peso diferente à cada cor (vermelho, azul e verde) da imagem. Como o olho humado é mais sensível as cores vermelho e verde, estas têm pesos maiores que a cor azul. O cálculo das cores usando o sistema de pesos é feito da seguinte maneira:

img = (77R + 151G + 28B)/256


<hr>
<h4>Versão serial</h4>

A versão serial foi feita usando inline assembly. Para desenvolvê-la, foi pego o código fonte base disponibilizado e feito mudanças no assembly para atender ao filtro escolhido. 
Primeiramente, o parâmetro R (Red) foi passado para eax e multiplicado por 77 (através do registrador ebx). Depois, o valor resultante foi atribuído ao registrador ecx. O mesmo processo foi repetido para os parâmetros G (Green) e B (Blue), cujas constantes de multiplicação foram 151 e 28, respectivamente. Por último, foi dividido o valor contido no registrador ecx (soma dos valores modificados de R, G e B) por 256 (soma das constantes de multiplicação, 77, 151 e 28). 

<img src="http://i.imgur.com/f6svIEg.png"></img>

<hr>
<h4>Versão SIMD</h4>


<hr>
<h4>Imagens testadas</h4>


<hr>
<h4>Comparação de desempenho</h4>


<hr>
<h4>Créditos</h4>

Projeto desenvolvido por Letícia Domingues (RA: 551724) na disciplina de Laboratório de Arquitetura e Organização de Computadores 2, ministrada pelo professor Ricardo Menotti.
