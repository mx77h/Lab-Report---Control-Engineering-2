# Laboranleitung

# Labor für Regelungstechnik

**Modellierung und Regelung von Drehzahl und Position eines Gleichstrommotors**

Bachelor – Mechatronik

Letzte Aktualisierung: 14. September 2026

---

## Inhaltsverzeichnis

1. Lernziel
2. Hardwareübersicht
3. Vorbereitungsaufgaben
4. Laboraufgaben
5. Bericht

---

## 1 Lernziel

Ein Gleichstrommotor ist ein elektromechanischer Aktor, der in der Automobilindustrie, Medizintechnik, industriellen Automatisierung, Unterhaltungselektronik, Haushaltsgeräten und Luft- und Raumfahrt weit verbreitet ist.

Das Lernziel dieses Labors ist die Identifikation eines elektromechanischen Systems anhand der Messung der Sprungantwort sowie der Entwurf eines geeigneten Reglers unter Verwendung von MATLAB Simulink und einem National Instruments Datenerfassungsgerät (NI DAQ). Im Verlauf des Labors muss das gemessene Signal für die weitere Verwendung aufbereitet und mit einem Standardglied approximiert werden. Folgende Schritte sind im Labor durchzuführen:

- Messung der Sprungantwort
- Systemidentifikation
- Entwurf eines PID-Reglers
- Simulation
- Implementierung

Diese Laborarbeit wendet Wissen aus den Lehrveranstaltungen „Regelungstechnik I & II" in Kombination mit „Analogschaltung" und „Mess- und Sensoriklabor" an.

---

## 2 Hardwareübersicht

### 2.1 Hardware

#### 2.1.1 Mechanischer Aufbau

Die Hardware umfasst ein Getriebe und einen Gleichstrommotor (Faulhaber 3257G012CR oder Maxon RE35 273752). Das Datenblatt des entsprechenden Motors befindet sich im Anhang 6. Die zu regelnde Größe ist die Winkelposition des Zeigers, der an der letzten Stufe befestigt ist. Die Winkelposition wird direkt auf der Abtriebswelle durch einen optischen Inkrementalgeber gemessen. Die Übertragung erfolgt über einen Riemenantrieb. Abbildung 1 zeigt das System mit beschrifteten Komponenten.

> **Warnung: Berühren Sie unter keinen Umständen bewegliche Teile der Hardware, da dies zu schweren Verletzungen führen kann!**

**Hinweis:** Für das Labor wurden vier verschiedene Boxen mit unterschiedlichen Übersetzungsverhältnissen *i* realisiert. Die Übersetzungsverhältnisse der einzelnen Boxen sind nachfolgend aufgeführt:

- Box 1 → i = 97,2
- Box 2 → i = 73,5
- Box 3 → i = 103,3
- Box 4 → i = 103,7

#### 2.1.2 Motortreiber

Der in diesem Labor verwendete Motortreiber ist der Cytron MD13S. Er ermöglicht die Drehzahlregelung des Motors über ein pulsweitenmoduliertes (PWM) Signal niedriger Leistung, das vom Digitalausgang der National Instruments (NI) PCIe-6321 DAQ-Karte erzeugt wird.

#### 2.1.3 Inkrementalgeber (Quadratur-Encoder)

Der in diesem Labor verwendete optische Encoder ist der Broadcom Avago HEDS-5500 A11. Er arbeitet als Inkrementalgeber, der Positionsänderungen optisch mit einer Auflösung von 500 Impulsen pro Umdrehung erfasst und die Winkelposition der Welle bestimmt. Durch Berücksichtigung der Abtastzeit und der Positionsänderung zwischen zwei Abtastungen kann die Winkelgeschwindigkeit des Zeigers berechnet werden. Zusätzlich bietet der Quadratur-Encoder zwei Kanäle zur Bestimmung der Drehrichtung. Das Datenblatt wurde in den entsprechenden Ressourcenordner auf Sakai hochgeladen.

#### 2.1.4 Elektrischer Aufbau

Das Elektronikgehäuse enthält einen Motortreiber und eine Platine, die die I/O-Pins des BNC-2090a-Moduls mit den entsprechenden Pins des Encoders und Motortreibers verbindet. Das BNC-2090a ist ein Frontpanel, das mit der PCIe-6321 DAQ-Karte verbunden ist, welche die Hardware steuert. Ein detaillierter Schaltplan, der die Verschaltung der einzelnen elektrischen Komponenten zeigt, ist in Abbildung 2 dargestellt.

---

## 3 Vorbereitungsaufgaben

Bitte bearbeiten Sie die folgenden Aufgaben zur Vorbereitung. Bringen Sie Ihre Vorbereitungsarbeit zur Laborsitzung mit, da Sie diese für die Identifikation und Regelung des realen Systems während der Sitzung benötigen.

### 3.1 Analytische Modellierung eines Gleichstrommotors

Abbildung 3 zeigt eine vereinfachte schematische Darstellung eines Gleichstrommotors. In diesem Beispiel wird der Motor als unbelastet betrachtet, sodass J_Last und b_Last gleich Null sind. Führen Sie eine White-Box-Modellierung durch, um die Übertragungsfunktion G_p(s) für einen Gleichstrommotor zu bestimmen. Leiten Sie bitte zwei Übertragungsfunktionen her:

- **G_p1(s):** Eingang: Spannung – Ausgang: Winkelverschiebung (Winkelposition)
- **G_p2(s):** Eingang: Spannung – Ausgang: Winkelgeschwindigkeit

Bestimmen Sie ein Zustandsraummodell für den Motor, wobei die Spannung der Eingang und die Winkelverschiebung der Ausgang ist. **Hinweis:** Sie können als Zustandsgrößen die Winkelverschiebung, die Winkelgeschwindigkeit und den Strom wählen.

### 3.2 Systemidentifikation

Bringen Sie die Lösungen der Übung 4-2 mit oder bearbeiten Sie die folgende Aufgabe. Die Datei *measurement_data.mat* im Sakai-Ordner enthält Messdaten der Sprungantwort eines beliebigen mechatronischen Systems. Die Zeit in Sekunden ist in der ersten Spalte aufgezeichnet. Die zweite Spalte enthält die Eingangswerte des Systems und die Ausgangswerte des Systems wurden in der dritten Spalte aufgezeichnet, beide in Volt. Beachten Sie, dass die Amplitude des Sprunganregungssignals nicht immer 1 beträgt.

- Stellen Sie die Rohmessdaten ähnlich wie in Abbildung 4 grafisch dar.
- Identifizieren Sie das System aus den Rohdaten als ein überdämpftes PT2-System.

---

## 4 Laboraufgaben

### 4.1 Hardware einrichten

Für dieses Labor wird ein Getriebe-System verwendet, das von einem Gleichstrommotor angetrieben und von der NI PCIe-6321 DAQ-Karte gesteuert wird. Um die Hardware für den Versuch einzurichten, müssen die folgenden Schritte durchgeführt werden:

1. Verbinden Sie den Spannungsausgang des Netzteils mit den entsprechend beschrifteten Buchsen des Geräts.
2. Verbinden Sie das SCSI-Kabel vom Elektronikgehäuse des Geräts mit dem NI BNC-2090a I/O-Modul.

### 4.2 Software einrichten

Der Hauptteil des Labors wird am Desktop-PC in den MCI VI-Laborräumen durchgeführt. Diese Labor-PCs sind mit NI PCIe-6321/6221 DAQ-Karten ausgestattet, die eine Echtzeitübertragung, -erfassung und -analyse von analogen und digitalen Daten ermöglichen. MATLAB Simulink wird für die Systemidentifikation, Simulation des Modells und Implementierung des Regelsystems verwendet. Dazu wird das Simulink Desktop Real-Time Add-On genutzt, um mit der NI PCIe-6321/6221 DAQ-Karte zu kommunizieren. Dies bietet eine einfache und verständliche Visualisierung von Regelsystemen bei gleichzeitig geringem Programmieraufwand.

Obwohl alle relevanten Daten und Software für dieses Labor vorinstalliert und eingerichtet sind, ist es ratsam, die nachstehende Checkliste durchzugehen, falls sich eine Komponente unerwartet verhält:

- Starten Sie MATLAB und öffnen und führen Sie die .m-Datei mit dem Namen „SystemID Setup" aus.
- Gehen Sie zum Panel „Desktop Real-Time" und klicken Sie auf „Hardware settings".
  - **Hinweis:** Wenn die Option nicht sofort sichtbar ist, erweitern Sie das Dropdown-Menü im Register „Apps" und suchen Sie dort danach.
- Gehen Sie zunächst zum Register „Solver" und:
  - Setzen Sie die Startzeit auf 0 und die Endzeit auf 1,5.
  - Stellen Sie unter „Solver settings" den Typ auf „Fixed-step" ein, klappen Sie „Solver details" auf und setzen Sie die „Fixed-step size" auf 0,0001 s.
- Klicken Sie anschließend auf das Register „Code Generation" und wählen Sie „sldrt.tlc" als „System target file" aus.

### 4.3 Identifikation des Systems

Öffnen Sie das Simulink-Modell „EncoderRead.slx" (siehe Abbildung 5) durch Ausführung des MATLAB-Skripts „SystemID Setup.m".

Ihre Aufgabe ist es, die Sprungantwort des Systems für eine Eingangsstufenhöhe von 12 V und ohne Verzögerung aufzuzeichnen. Verbinden Sie die bereitgestellten Elemente entsprechend, um dies zu erreichen.

**Hinweis:** Beachten Sie, dass der Scope-Block die Winkelgeschwindigkeit ω in Umdrehungen pro Minute (U/min) und die Winkelposition θ in Grad misst. Die Messdaten werden nach Abschluss des Messvorgangs in den MATLAB-Workspace protokolliert.

Nach der Messung der Sprungantwort des Systems bestimmen Sie zwei Übertragungsfunktionen des Systems mit dem Gleichstrommotor durch Anwendung einer Methode der kleinsten Quadrate (Least-Square-Fitting).

**Hinweis:** Berücksichtigen Sie die Einheit der Messdaten, auf deren Grundlage das System modelliert wird. Um die Box mit Sollwerten in Grad (Winkelposition) regeln zu können, muss eine Umrechnung von U/min in rad/s durchgeführt werden.

Die allgemeine Form der PT2-Übertragungsfunktion ist in Gleichung 1 gegeben:

**PT2(s) = K / ((τ₁·s + 1)(τ₂·s + 1))**  — (Gl. 1)

Stellen Sie die Sprungantwort der identifizierten Übertragungsfunktion für eine Eingangsspannung von 12 V grafisch dar und vergleichen Sie sie mit der gemessenen Sprungantwort. Was ist die Ausgangsgröße für dieses System 2. Ordnung? Ihre Ergebnisse sollten in etwa wie Abbildung 6 aussehen.

Da wir die Position θ des Zeigers regeln möchten, müssen wir die geschätzte Übertragungsfunktion G_p(s) des Modells anpassen. Dies muss geschehen, da die Messdaten die Winkelgeschwindigkeit ω des Zeigers für eine bestimmte Eingangsspannung u beschreiben. Der Zusammenhang ist in Gleichung 2 gegeben:

**PT3(s) = G_p(s) = Θ(s)/U(s) = Ω(s)/(s·U(s)) = (1/s)·PT2(s)**  — (Gl. 2)

### 4.4 Reglerentwurf

Entwerfen Sie einen PID-Regler für ein geschlossenes Regelsystem durch Anwendung der Ziegler-Nichols-Methode für das identifizierte System und simulieren Sie das geschlossene Regelsystem.

**Hinweis 1:** Bei Methode 1 können die benötigten Parameter aus der Sprungantwort des Systems abgelesen werden.

**Hinweis 2:** Bei Methode 2 müssen Sie die MATLAB-Funktion „rlocus()" auf Basis Ihrer Übertragungsfunktion verwenden, um die kritische Verstärkung K_kr zu finden, und ein weiteres geschlossenes Regelsystem mit P-Regler in einem leeren Simulink-Modell entwerfen (wie in Abbildung 7 dargestellt), um die Periodendauer P_kr aus dem Ausgangssignal zu ermitteln.

Nach dem Erhalt eines Modells des Systems und des PID-Reglers können wir die Leistung des geschlossenen Regelsystems simulieren und den Eingang R(s), den Fehler E(s), die Stellgröße U(s) und den Ausgang Θ(s) mit dem Scope-Block messen. Bitte fügen Sie R2D-Blöcke (Radiant zu Grad) und D2R-Blöcke (Grad zu Radiant) ein, wie in Abbildung 8 dargestellt.

### 4.5 Reglerimplementierung und -bewertung

Fahren Sie nach der Simulation des entworfenen geschlossenen Regelsystems mit PID-Regler mit der Implementierung des Regelsystems unter Verwendung von Simulink Desktop Real-Time fort. Öffnen Sie die MATLAB-Datei „RunController.m", geben Sie die PID-Verstärkungskoeffizienten wie im Code angegeben ein und führen Sie die Datei aus. Das Ihnen präsentierte Blockdiagramm ist unvollständig. Vervollständigen Sie daher das Blockdiagramm und wenden Sie eine Anti-Windup-Methode (z. B. Clamping) in Ihrem PID-Regler an.

Beobachten Sie das Verhalten des realen Systems und beantworten Sie die folgenden Fragen:

- Verhält es sich wie erwartet? Wenn nicht, wo weichen Ihre Beobachtungen von Ihren Erwartungen ab?
- Passen Sie die Kp-, Ki- und Kd-Verstärkungen an und beschreiben Sie dann, wie diese Anpassungen die Leistung der Positionsregelung beeinflussen.

---

## 5 Bericht

Erstellen Sie einen Bericht mit maximal 10 Seiten, der umfassende Erklärungen für alle Vorbereitungsaufgaben und Laboraufgaben durch Berechnungen und Zeichnungen enthält. Bitte achten Sie darauf, Ihre Überlegungen, Vorgehensweise, Ergebnisse und Interpretationen wissenschaftlich zu dokumentieren. Berücksichtigen Sie folgende Aspekte bei der Erstellung des Berichts:

- Der Bericht soll den MCI-Richtlinien für die Dokumentation von Laboraktivitäten entsprechen. Bitte halten Sie ihn so kurz wie möglich und stellen Sie gleichzeitig sicher, dass alle relevanten Informationen enthalten sind.
- Die im Labor gesammelten Daten sollen mit detailliertem Kommentar zu den Messergebnissen analysiert werden, wobei diese mit theoretischen Erwartungen und Simulationen verglichen werden.
- Am Ende des Berichts sollte ein Abschnitt für Schlussfolgerungen und Diskussion stehen.

Der Bericht ist bis zum Abgabetermin auf Sakai – Assignments einzureichen. Bitte geben Sie auf dem Deckblatt das Labordatum, die Gruppenmitglieder und weitere wichtige Informationen an.
