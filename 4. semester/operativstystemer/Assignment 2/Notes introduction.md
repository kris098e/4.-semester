Start from the provided source code or take inspiration. The code given is a starting point

interract with the driver like a file i.e `echo "hello" > /dev/scull0` and cat it aswel

# start
med at forstå koden til scull

kopir fra pipe og modificer det så det bruger 2 buffere.

ioctl til at modificere antal readers og buffer size, include libary
bruges når man har åbnet en pipe til det modul i sit c-program, så kan man modificere med ioctl.

# test
at man kan skrive og læse det samme ud. Test også hvis man skriver så opdateres hvor der står, f.eks. hvis man skriver 2 gange med forskelligt indhold, så test det fungerer som FIFO? (Hvis det er FIFO).
test at hvis man har nonblocking IO at man kan skrive med det samme. Test at hvis man har blocking, at man så muligvis venter.
test hvis man sætter buffer lavt, så kan man ikke skrive over