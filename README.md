# Chat - простой чат
Легковесное приложение для обмена текстовой информацией между пользователями.

# Скриншоты
**Страница авторизации**  
![screenshots 1](https://github.com/EDIT89/Chat/blob/main/.github/LoginPage.png)  

**Страница регистрации**  
![screenshots 2](https://github.com/EDIT89/Chat/blob/main/.github/SignUpPage.png)  

**Список диалогов**  
![screenshots 3](https://github.com/EDIT89/Chat/blob/main/.github/Dialogs.png)  

**Список доступных пользователей**  
![screenshots 4](https://github.com/EDIT89/Chat/blob/main/.github/UsersPage.png)  

**Страница общения**  
![screenshots 5](https://github.com/EDIT89/Chat/blob/main/.github/Conversation.png)  

## Требования приложения
+ Windows 7/10
+ VPN-соединение между сервером и клиентом

# Архитектура
![screenshots 6](https://github.com/EDIT89/Chat/blob/main/.github/App%20architecture.png)  

Приложение предоставляет пользователям удобный способ отправки и просмотра данных, 
которые приходят от других пользователей с помощью бекенда Server.

В приложении нет сложных алгоритмов обработки данных, основная работа с 
"предметной областью" и данными происходит на бекенде.

## Директории проекта
Эта секция коротко описывает основные директории в структуре проекта.

### `src/Engine`

Здесь находятся функции которые создают QML-компоненты.

### `src/Pages`

В этой директории находится файлы с описанием функционала
всех страниц в `StackView` приложения.

### `src/ServerWorker`

Здесь расположены функции которые обрабатывают сообщения исходящие от сервера.

### `src/Structures`

Описание структур, которые используются для заполения моделей.

### `src/Qml/Pages`

Здесь находятся модули с описанием визуального интерфейса страниц, 
расположенных в `StackView`.

### `src/Qml/Items`

В этой директории находятся все кастомные компоненты для модулей в `src/Qml/Pages`.

### `src/Qml/Images`

Здесь расположены иконки для кастомицазии объектов визуального интерфейса приложения. 

### `.github`

Здесь расположены ресурсы которые используются для формирования файла README.md.


[![GitHub](https://img.shields.io/badge/-Мой_GitHub-333?style=for-the-badge&logo=GitHub&logoColor=fff)](https://github.com/EDIT89)
