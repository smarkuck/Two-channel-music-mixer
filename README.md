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

Dodałem osobnego brancha do wykresów, żeby się na niego przełączyć pobierzcie repo normalnie, wejdźcie do folderu z nim a potem wklepcie:
```
git checkout origin soundGraph
```

Dodałem następnego brancha do zapisywania akcji. Nie wiem czy o to chodziło ale jest w wersji demo :)
Jak pobierzecie repo to po wczytaniu utworu spróbujcie załadować akcje test.acn i po odpaleniu powinny się suwaki same przesuwac.



----------

Dodałam pobieranie w formacie mp3 ale ono się opiera na bibliotece zewnętrznej libmp3lame.so, ona jest w folderze mixer,
jak będzie wam wyskakiwał błąd że jakieś undefined references do funkcji z lame w nazwie to trzeba kliknąć prawym przyciskiem na nazwę projektu->Add Libraries->Add external libraries 
i wybrać tą bibliotekę i powinno być ok