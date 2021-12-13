# Hotellihuoneen varausohjelma

### C++ konsoli ohjelma. **Toteutettu 4-5 pisteen vaatimusten mukaan**
---
## Ohjelman kulku
Ohjelmalla käyttäjä pystyy varata hotellihuoneita sekä tehdä hakuja tehtyihin varauksiin. Varausten teko toimii valikkojen avulla, joista käyttäjä valitsee haluamansa toiminnon syöttämällä kyseisen valinnan numeron.

Varausten teossa käyttäjälle ilmoitetaan vapaiden huoneiden lukumäärä ja käyttäjältä kysytään, haluaako hän valita varattavan huonenumeron itse vai generoida sen.

**HUOM!** Huoneen tyyppi eli siis se, onko huone yhdelle vai kahdelle ihmiselle määritellään pelkän huonenumeron avulla. Jos huoneita olisi yhteensä 100 kpl, ja jos käyttäjä valitsee huonenumeron 1 - 50, huoneen tyyppi on yhden hengen huone. Jos taas käyttäjä valitsee huonenumeron 51 - 100, on huoneen tyyppi silloin kahden hengen huone.

Kun huonenumero on valittu, käyttäjältä kysytään kuinka monta yötä hän haluaa yöpyä. 

Tämän jälkeen käyttäjltä kysytään tarvittavat yhteystiedot (pelkkä nimi).

Kun tarvittavat yhteystiedot on saatu, ohjelma generoi käyttäjälle satunnaisen varausnumeron ja ilmoittaa lopullisen laskun määrän. Laskusta vähennetään alennus jos sellainen on satunnaisesti generoitu.

Varaus on nyt valmis ja tallennettu struct-taulukkoon ja käyttäjä palautetaan päävalikkoon, josta tallennettua varausta voi hakea varausnumeron tai nimen perusteella.

## Toteutetut toiminnot

- Ohjelman alussa huoneita generoidaan satunnainen parillinen määrä väliltä 40 - 300.
- Käyttäjä voi valita varattavan huoneen itse tai generoida sen satunnaisesti.
- Ohjelma arpoo, annetaanko huoneiden loppuhintaan alennus vai ei.
- Ohjelma tarkistaa aina, että huone on varattavissa.
- Varauksia voidaan etsiä joko varaajan nimen perusteella tai varausnumerolla.