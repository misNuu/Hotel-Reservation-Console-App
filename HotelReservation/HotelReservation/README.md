# **Hotellihuoneen varausohjelma**

### C++ konsoli ohjelma. **Toteutettu 4-5 pisteen vaatimusten mukaan**
---
## **Ohjelman yleiskatsaus**
Ohjelmalla käyttäjä pystyy varata hotellihuoneita sekä tehdä hakuja tehtyihin varauksiin. Varausten teko toimii valikkojen avulla, joista käyttäjä valitsee haluamansa toiminnon syöttämällä kyseisen valinnan numeron. Varauksia pystyy tehdä niin paljon kuin huoneita on vapaana.


### **Ohjelman kulku**
1. Päävalikosta käyttäjä valitsee halutun toiminnon. Sieltä päästään varauksen tekemiseen, varausten hakuihin sekä huoneiden hinnaston voi tarkistaa.
2. Varausten teon yhteydessä käyttäjälle ilmoitetaan vapaiden huoneiden lukumäärä ja käyttäjältä kysytään, haluaako hän valita varattavan huonenumeron itse vai generoida sen.

    >**HUOM!** Huoneen tyyppi (1-, 2- hengen huone) määritellään pelkän huonenumeron perusteella. Esim. jos huoneita olisi yhteensä 100 kpl, ja käyttäjä valitsee huonenumeron 1-50 väliltä, huoneen tyyppi on yhden hengen huone. Jos taas käyttäjä valitsee huonenumeron 51-100 väliltä, on huoneen tyyppi silloin kahden hengen huone.

3. Kun huonenumero on valittu, käyttäjältä kysytään kuinka monta yötä hän haluaa yöpyä. 

4. Tämän jälkeen käyttäjältä kysytään tarvittavat yhteystiedot (pelkkä nimi riittää tässä ohjelmassa).

5. Kun tarvittavat yhteystiedot on saatu, ohjelma generoi käyttäjälle satunnaisen varausnumeron ja ilmoittaa lopullisen laskun määrän. Laskusta vähennetään alennus jos sellainen on satunnaisesti generoitu.

6. Varaus on nyt valmis ja tallennettu struct-taulukkoon ja käyttäjä palautetaan päävalikkoon, josta tallennettua varausta voi hakea varausnumeron tai nimen perusteella.

### **Toteutetut toiminnot**

- Ohjelman alussa huoneita generoidaan satunnainen parillinen määrä väliltä 40 - 300.
- Käyttäjä voi valita varattavan huoneen itse tai generoida sen satunnaisesti.
- Ohjelma arpoo, annetaanko huoneiden loppuhintaan alennus vai ei.
- Varauksia voidaan etsiä joko varaajan nimen perusteella tai varausnumerolla.
- Varauksia voi tehdä niin paljon kuin huoneita on vapaana.
- Syötteen tarkistus.