Filtry częstotliwości:
[Audio EQ Cookbook](http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt)
[Przykłady](http://blog.bjornroche.com/2012/08/basic-audio-eqs.html)

Przycisk Play działa dopiero po chwili jak już utwór się załaduje.

do odtwarzania mp3 potrzebny jest gstreamer1.0-plugins-ugly
```
sudo apt-get install gstreamer1.0-plugins-ugly
```

jak dalej nie będzie szło to jeszcze któreś z tych spróbujcie zainstalować 
```
libgstreamer1.0-0
gstreamer1.0-plugins-base
gstreamer1.0-plugins-good
gstreamer1.0-plugins-bad 
gstreamer1.0-libav
gstreamer1.0-doc
gstreamer1.0-tools
```

no i zanim udało mi się skompilować aplikację poprawnie musiałem doinstalować jakieś programiki których już nie pamiętam, stackoverflow pomoże a jak nie to piszcie

jak będziecie dołączać nowe klasy z QT to patrzcie czy w dokumentacji nie pisze żeby dodać w pliku mixer.pro linijki w stylu `QT += multimedia` bo miałem z tym problem