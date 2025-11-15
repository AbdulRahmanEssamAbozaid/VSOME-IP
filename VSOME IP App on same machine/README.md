# Version 1: GitHub Pro Style

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/3/3a/SomeIP_Blue_Logo.png" alt="vSomeIP Banner" width="600"/>
</p>

<h2 align="center">🔥 vSomeIP Demo — Request/Response + Clean Shutdown</h2>

<p align="center">
  <b>Server ↔ Client communication using vSomeIP | Reliable Shutdown | Clean Logging</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B14-blue"/>
  <img src="https://img.shields.io/badge/vSomeIP-Working-green"/>
  <img src="https://img.shields.io/badge/Target-AUTOSAR%20Adaptive-orange"/>
  <img src="https://img.shields.io/badge/Platform-Linux%20%7C%20Ubuntu-darkgreen"/>
</p>

---

## 📌 Overview

This is a clean and minimal **vSomeIP request/response demo**:

* The **Client** sends a request using `METHOD_ID`.
* The **Server** responds with: `"Hello From Server"`.
* The **Client** sends a **reliable shutdown** message using `METHOD_SHUTDOWN`.
* Both applications stop gracefully.

This project is a fully working vSomeIP demo that includes:

A minimal Server offering a service

A minimal Client requesting the service

Clean & short colored logs

Unified vsomeip.json configuration

CMake build system

Simple, readable code structure

Suitable for learning AUTOSAR SOME/IP communication and testing service discovery, request/response, reliable/unreliable messaging.

---

## 📂 Project Structure

```
vsomeip-demo/
├── CMakeLists.txt
├── README.md
├── config/
│   └── vsomeip.json
├── include/
│   └── common.hpp
│   ├──client.hpp
│   ├──server.hpp
│   └──coloers.hpp
└── src/
    ├── server.cpp
    └── client.cpp
```

---
🔧 Requirements

Ubuntu 20.04+ or any Linux distro

CMake >= 3.10

g++ >= 9

vSomeIP installed:
```bash
    sudo apt install libvsomeip3* -y
```
## 🧩 Build

```bash
mkdir build && cd build
cmake ..
make -j
```

---

## 🚀 Run

Open two terminals:

### 1️⃣ Start the server

```bash
VSOMEIP_CONFIGURATION=../config/vsomeip.json ./server
```

### 2️⃣ Start the client

```bash
VSOMEIP_CONFIGURATION=../config/vsomeip.json ./client
```

---

## 📝 Expected Output

### **Server**

```
[SERVER] Offer service done. Waiting for client...
[SERVER] Request received. Sending response...
[SERVER] Response sent.
[SERVER] Shutdown request received. Stopping...
```

### **Client**

```
[CLIENT] Waiting for response...
[CLIENT] Sending request...
[CLIENT] Response received: Hello From Server
[CLIENT] Sending shutdown request...
```
---

```
+--------------------+         +------------------+
|     Client App     |         |    Server App    |
|--------------------|         |------------------|
| RequestService     |  -->    | OfferService     |
| Send(Method_ID)    |         | Handle Request   |
| Receive(Response)  | <--     | Send Response    |
| Send(Shutdown)     |  -->    | Stop Application |
+--------------------+         +------------------+
```

---

## 🛠️ Troubleshooting

### ❗ local_client_endpoint::max_allowed_reconnects_reached

احذف أي ملفات سوكيت قديمة:

```bash
rm -rf /tmp/vsomeip-*
```

### ❗ Different ports or configs

تأكد أن:

* السيرفر والكلاينت يستخدمون **نفس vsomeip.json**
* نفس `service`, `instance`, `reliable`, `unreliable`
* نفس أسماء الـ Application

---

# Version 4: Automotive Engineering Style

## 🔧 vSomeIP Demo — Automotive Communication Module

هذا المشروع يوضح نموذج اتصال يعتمد على **Some/IP** مطابق لأسلوب الأنظمة المستخدمة داخل السيارات.

يتم استخدام **Request/Response Service Interface** كالتالي:

* Service ID: `0x1234`
* Instance ID: `0x5678`
* Methods:

  * `0x0421` → Normal Request
  * `0x9999` → Shutdown Command

---

## 1. System Description

يقوم السيرفر بعمل **OfferService** للـ Service، بينما يقوم الكلاينت بعمل **RequestService** ثم يبدأ في إرسال **Method Call**.

التواصل يكون على شكل:

1. Client → Server: Method Request
2. Server → Client: Method Response
3. Client → Server: Shutdown Method (TCP/Reliable)

يتم إنهاء التطبيقات بشكل **منضبط وآمن** (Graceful Shutdown) لضمان عدم ترك Socket resources معلّقة.

---

## 2. Software Architecture

```
+--------------------+         +------------------+
|     Client App     |         |    Server App    |
|--------------------|         |------------------|
| RequestService     |  -->    | OfferService     |
| Send(Method_ID)    |         | Handle Request   |
| Receive(Response)  | <--     | Send Response    |
| Send(Shutdown)     |  -->    | Stop Application |
+--------------------+         +------------------+
```

---

## 3. Build Instructions

```bash
mkdir build && cd build
cmake ..
make -j
```

---

## 4. Execution

### Server

```bash
VSOMEIP_CONFIGURATION=../config/vsomeip.json ./server
```

### Client

```bash
VSOMEIP_CONFIGURATION=../config/vsomeip.json ./client
```

---

## 5. Expected Behavior Summary

| Component  | Action                                                                    |
| ---------- | ------------------------------------------------------------------------- |
| **Server** | Offers service, receives request, responds, stops on shutdown             |
| **Client** | Requests service, sends method call, receives response, triggers shutdown |

---

## 6. Engineering Notes

* يجب التأكد من **تطابق Service/Instance IDs** بين الـ ECU modules.
* يجب مسح ملفات الـ socket القديمة قبل التشغيل:

```bash
rm -rf /tmp/vsomeip-*
```

* يستخدم المشروع Reliable Channel (TCP) للـ Shutdown لضمان وصول الرسالة.

---

## 7. Compliance & Use Cases

* مناسب كمثال لتطبيق vSomeIP في:

  * AUTOSAR Adaptive Communication
  * ECU-to-ECU Messaging
  * Service-Oriented Architecture Automotive Middleware

---

## 📘 End of Document

يمكنك الآن اختيار النسخة الأفضل لك: **GitHub Pro** أو **Automotive Engineering Style**.

# VSOMEIP Project — Two README Versions

Below you will find **Version 1** (full detailed professional README) and **Version 4** (clean ultra-minimal professional README).
Choose whichever fits your GitHub style.

---

# ✅ **Version 1 — Full, Detailed, Professional README**

## 🚗 VSOMEIP Demo Project

This project demonstrates a minimal yet complete communication flow using **SOME/IP** with the **vsomeip** middleware. The setup includes:

* Server Application
* Client Application
* Request/Response Handling
* Shutdown Mechanism
* Full CMake Build System

---

## 📦 Project Structure

```
vsomeip-demo/
│── CMakeLists.txt
│── config/
│   ├── server.json
│   ├── client.json
│── include/
│   └── common.hpp
│── server/
│   └── server.cpp
│── client/
│   └── client.cpp
└── README.md
```

---

## ⚙️ Requirements

Before building, ensure you have:

* GCC / Clang
* CMake 3.10+
* Boost libraries
* vsomeip installed on your system

Install vsomeip (Ubuntu example):

```bash
git clone https://github.com/COVESA/vsomeip.git
cd vsomeip
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

---

## 🛠️ Build Instructions

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

Outputs:

* `server-app`
* `client-app`

---

## 🧩 Configuration Files

### `server.json`

Defines offered service.

### `client.json`

Defines requested service.

Both follow the standard vsomeip configuration structure.

---

## 📡 Running the Demo

### 1️⃣ Start the server

```bash
./server-app
```

Expected:

```
[SERVER] Waiting for client...
```

### 2️⃣ Start the client

```bash
./client-app
```

Expected:

```
[CLIENT] Received: Hello From Server
```

---

## 🔁 Communication Flow

1. Client sends request → Server
2. Server responds with: `Hello From Server`
3. Client prints the received message
4. Client sends shutdown request to server
5. Server gracefully terminates

---

## 📝 Common.hpp

Contains all shared SOME/IP IDs:

```cpp
namespace SomeIPConfig {
    const vsomeip::service_t SERVICE_ID = 0x1111;
    const vsomeip::instance_t INSTANCE_ID = 0x2222;
    const vsomeip::method_t METHOD_ID = 0x3333;
    const vsomeip::method_t METHOD_SHUTDOWN = 0x4444;
}
```

---

## 📜 License

MIT License.

---



# vSomeIP Demo Project (Server + Client)

## 🚀 Overview

This project is a **fully working vSomeIP demo** that includes:

* A minimal **Server** offering a service
* A minimal **Client** requesting the service
* Clean & short **colored logs**
* Unified `vsomeip.json` configuration
* CMake build system
* Simple, readable code structure

Suitable for learning AUTOSAR SOME/IP communication and testing service discovery, request/response, reliable/unreliable messaging.

---

## 📁 Project Structure

```
vsomeip-demo/
│── CMakeLists.txt
│── vsomeip.json
│── README.md
│
├── server/
│   ├── server.cpp
│   └── CMakeLists.txt
│
├── client/
│   ├── client.cpp
│   └── CMakeLists.txt
```

---

## 🔧 Requirements

* Ubuntu 20.04+ or any Linux distro
* CMake >= 3.10
* g++ >= 9
* vSomeIP installed:

  ```bash
  sudo apt install libvsomeip3* -y
  ```

---

## ⚙️ Building the Project

From project root:

```bash
mkdir build && cd build
cmake ..
make -j4
```

Output binaries:

```
build/server/server
build/client/client
```

---

## ▶️ Running the Demo

### 1️⃣ Start the server

```bash
./server/server
```

Expected log:

```[32m[SERVER][0m Service offered. Waiting for client...
```

### 2️⃣ Start the client

```bash
./client/client
```

Expected log:

```[34m[CLIENT][0m Request sent.
[32m[CLIENT][0m Response received.
```

---

## 🧩 Configuration (vsomeip.json)

```json
{
  "unicast": "127.0.0.1",
  "logging": {
    "level": "error",
    "console": "true",
    "file": { "enable": "false" }
  },
  "applications": [
    { "name": "server-app", "id": "0x1111" },
    { "name": "client-app", "id": "0x2222" }
  ],
  "services": [
    {
      "service": "0x1234",
      "instance": "0x5678",
      "reliable": "30490",
      "unreliable": "30491"
    }
  ]
}
```

Make sure to export it before running:

```bash
export VSOMEIP_CONFIGURATION=./vsomeip.json
export VSOMEIP_APPLICATION_NAME=server-app   # or client-app
```

---

## 🖥️ Server Code (Snippet)

```cpp
std::cout << "\033[32m[SERVER]\033[0m Offer service done. Waiting for client..." << std::endl;
```

---

## 🖥️ Client Code (Snippet)

```cpp
std::cout << "\033[34m[CLIENT]\033[0m Request sent" << std::endl;
```

---

## 🧱 Architecture Diagram

```
   +-----------+           SOME/IP           +-----------+
   |  CLIENT   | --------------------------> |  SERVER   |
   | Req (RTE) | <-------------------------- | Resp (SD) |
   +-----------+                             +-----------+
```

---

## ⭐ Features

* Clean minimal vSomeIP setup
* Colored logs for clarity
* Simple CMake & folder structure
* Works instantly with no dependencies conflicts

---

## 📌 Notes

* Works on localhost only
* Easy to extend for events, fields, or SD

---

## 📜 License

MIT
