# Automat do napojów

![Case image](/images/case_image.png)


## Funkcjonalność

- Pomiar wysokości kubka na podstawie wykrywania odległości do dna kubka oraz jego krawędzi
- Nalewanie cieczy z uwzględnieniem maksymalnej bezpiecznej wysokości nalanej cieczy
- Sterowanie menu LCD poprzez enkoder z przyciskiem
- Wybór proporocji dwóch nalewanych cieczy
- Manualne sterowanie silnikami pomp
- Manualne sterowanie serwomechanizmem z zamontowanym czujnikiem odległości
- Odczyt odległości z czujnika


## Wykorzystane elementy

- Płytka STM32F407G-DISC1
- Zasilacz 12V/3A
- 2 przetwornice step-down, 12V -> 3V oraz 12V -> 5V
- Czujnik odległości VL53l0X
- Serwomechanizm SG90s
- Dwukanałowy sterownik silników L293D
- 2 pompy membranowe R385
- Wyświetlacz LCD TFT 1,8'' - Waveshare 13892
- Enkoder z przyciskiem - Waveshare 9533



## Wykorzystane piny

### Enkoder

| Moduł         | Układ         | Wykorzystanie |
| ------------- | ------------- | ----- |
| SIA           | PE9           | obrót enkodera (TIM1 Encoder mode CH1+CH2) |
| SIB           | PE11          | obrót enkodera (TIM1 Encoder mode CH1+CH2) |
| SW            | PB12          | Przycisk enkodera (EXTI12, pull-up, falling edge trigger detection) |
| GND           | GND           | Masa |
| VCC           | 3V            | Zasilanie |

### Ekran LCD

| Moduł         | Układ         | Wykorzystanie |
| ------------- | ------------- | ----- |
| VCC           | 3V            | Zasilanie |
| GND           | GND           | Masa |
| DIN           | PA7           | Linia danych (SPI1) |
| CLK           | PA5           | Linia zegarowa (SPI1) |
| CS            | PD7           | Chip select, (GPIO output) |
| DC            | PC4           | Wybór danych, (GPIO output) |
| RST           | PA9           | Reset układu, (GPIO output) |
| BL            | -             | Podświetlenie - nieużywane |

### Czujnik odległości

| Moduł         | Układ         | Wykorzystanie |
| ------------- | ------------- | ----- |
| VCC           | 3V            | Zasilanie |
| GND           | GND           | Masa |
| SCL           | PB6           | linia zegara (I2C1, pull-up) |
| SDA           | PB7           | linia danych (I2C1, pull-up) |
| GPIO1         | PC1           | Obsługa przerwania EXTI1 oznaczającego nadchodzący wynik pomiaru (pull-up) |
| XSHUT         | -             | Aktywacja czujnika - nieużywane |

### Serwomechanizm

| Moduł         | Układ         | Wykorzystanie |
| ------------- | ------------- | ----- |
| PWM           | PE5           | PWM (TIM9 CH1) |
| VCC           | 5V            | Zasilanie |
| GND           | GND           | Masa |

### L293D

| Moduł         | Układ         | Wykorzystanie |
| ------------- | ------------- | ----- |
| ENABLE1       | PB14          | Sterowanie działaniem silnika 1 (GPIO output, pull-down) |
| INPUT1        | 5V            | Kierunek silnika 1 |
| OUTPUT1       | Pompa         | Zasilanie pompy |
| GND           | GND           | Masa |
| GND           | GND           | Masa |
| OUTPUT2       | Pompa         | Masa pompy |
| INPUT2        | GND           | Kierunek silnika 1 |
| Vs            | 12V           | Zasilanie układu |
| ENABLE2       | PB15          | Sterowanie działaniem silnika 2 (GPIO output, pull-down) |
| INPUT3        | 5V            | Kierunek silnika 2 |
| OUTPUT3       | Pompa         | Zasilanie pompy |
| GND           | GND           | Masa |
| GND           | GND           | Masa |
| OUTPUT4       | Pompa         | Masa pompy |
| INPUT4        | GND           | Kierunek silnika 2 |
| Vss           | 5V            | Zasilanie logiki |


## Timery

- TIM1 - obsługa enkodera w trybie Encoder Mode (CH1 + CH2)
- TIM3 - obsługa procedury mierzenia oraz nalewania cieczy podczas przerwania
- TIM7 - debouncing przycisku enkodera
- TIM9 - PWM serwomechanizmu (CH1)



## Części 3D

Wszystkie części zostały zaprojektowane w Fusion 360 i wydrukowane na drukarce 3D.

Większość wymiarów jest sparametryzowana i można dowolnie zmieniać rozmiar elementów obudowy, ramienia montowanego na serwomechanizmie oraz rurek łączących rurki silikonowe.



## Autorzy

- Tymon Jakubowski - @tjakubowski
- Kamil Mosek - @kamilmosek
- Mateusz Olejnik - @molejnik1998