estaChovendo.
naotenhoGuardaChuva.

!comprarGuardaChuva.
!naoPegarChuva.

+!comprarGuardaChuva: estaChovendo & naotenhoGuardaChuva <- .printf("sair");
.printf("procurarLoja");
.printf("comprarGuardaChuva").

+!naoPegarChuva: not estaChovendo <- .printf("sair");
.printf("jogarBola").

+!naoPegarChuva: estaChovendo & naotenhoGuardaChuva <- .printf("ficarEmCasa");
.printf("estudar").

