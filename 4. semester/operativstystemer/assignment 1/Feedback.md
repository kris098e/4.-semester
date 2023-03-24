Fin video.  
  
Du har memory leaks på linje 35, fordi du glemmer at frigøre din msg_t, når allokering af din besked fejler.  
  
Flot rapport. Husk at nævn i designafsnittet, at du har truffet et valg om, at man ikke kan indsætte ""halve"" beskeder på stakken. Man kan jo selv vælge, om man vil tillade, at enkelte bytes ikke bliver kopieret med eller ej. Dette er et valgt, du har truffet :) Vær generelt opmærksom på forskellen mellem design- og implementeringsafsnit. Du skal addresse concurreny i designafsnittet på højt niveau (dvs. ikke tale om local_irq_save) såsom at ""flere processor kan ikke tilgå postkassen samtidig"", og derefter argumentere for, hvordan du opfylder det i implementeringsafsnittet. Det er pedanteri, men stadigvæk væsentligt :)  
Rigtig godt testafsnit med tidsstempler og fin forståelse for critical section-problemet.  
  
Fortsæt det gode arbejde!