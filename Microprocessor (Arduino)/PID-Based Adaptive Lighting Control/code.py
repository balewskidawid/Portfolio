import machine
import time

# Klasa PID
class PID:
    def __init__(self, kp, ki, kd, integral_limit=1000, dead_zone=8):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.prev_error = 0
        self.integral = 0
        self.integral_limit = integral_limit  # Ograniczenie dla składowej całkowej
        self.dead_zone = dead_zone  # Martwa strefa

    def compute(self, setpoint, current_value):
        # Odwrócony błąd
        error = current_value - setpoint  # Logika odwrócona, aby działała poprawnie

        # Martwa strefa: ignorowanie małych błędów
        if abs(error) < self.dead_zone:
            error = 0

        # Ograniczenie integralnej składowej (Anti-Windup)
        self.integral += error
        self.integral = max(-self.integral_limit, min(self.integral, self.integral_limit))

        # Obliczenie pochodnej błędu
        derivative = error - self.prev_error

        # Obliczenie wyjścia PID
        pwm_output = self.kp * error + self.ki * self.integral + self.kd * derivative

        # Ograniczenie wyjścia do zakresu PWM
        pwm_output = clamp(pwm_output, 0, 1023)

        # Debugowanie PID
        #print(f"DEBUG | Error: {error}, Integral: {self.integral}, Derivative: {derivative}, PWM Output: {pwm_output}")

        # Zaktualizowanie poprzedniego błędu
        self.prev_error = error

        return pwm_output

# Funkcja ograniczająca wartości (np. dla PWM)
def clamp(value, min_value, max_value):
    return max(min_value, min(max_value, value))
# Konfiguracja przycisku na GPIO2 (D4)
button_pin = machine.Pin(2, machine.Pin.IN, machine.Pin.PULL_UP)

# Stan sterowania lampką
lamp_enabled = True

# Konfiguracja lampki (PWM na GPIO14 - D5)
lamp_pin = machine.Pin(14, machine.Pin.OUT)
pwm_lamp = machine.PWM(lamp_pin)
pwm_lamp.freq(1000)  # Częstotliwość PWM na 1kHz

# Konfiguracja ADC (fotorezystor na A0)
adc = machine.ADC(0)  # Pin A0

# Ustawienia PID
kp = 1.03   # Wzmocnienie proporcjonalne
ki = 0.000001  # Wzmocnienie całkowe
kd = 0.5  # Wzmocnienie różniczkowe
pid = PID(kp, ki, kd, integral_limit=500, dead_zone=10)

# Stały poziom światła, który chcemy osiągnąć
setpoint = 30  # Docelowy poziom światła (w jednostkach odczytu fotorezystora)

# Funkcja obsługująca przycisk
def button_callback(pin):
    global lamp_enabled
    lamp_enabled = not lamp_enabled  # Przełączanie stanu lampki (włącz/wyłącz)

# Rejestracja obsługi przerwania dla przycisku
button_pin.irq(trigger=machine.Pin.IRQ_FALLING, handler=button_callback)

# Pętla główna
while True:
    
    # Odczyt wartości z fotorezystora (światło zewnętrzne)
    light_value = adc.read()

    # Obliczenie wartości PWM na podstawie odwróconego błędu PID
    pwm_value = pid.compute(setpoint, light_value)  # Odwrócenie logiki błędu

    # Ustawienie jasności lampki
    pwm_lamp.duty(int(pwm_value))
    
    # Debugowanie
    print(f"Light Value: {light_value}, PWM Output: {pwm_value}")
    time.sleep(0.1)  # Skrócone opóźnienie dla szybszej reakcji
