# Settings Config.md

Документация по формату конфигурационного файла для системы настройки отдачи и разброса оружия (Guns Recoil).

---

## 1. Обзор

Конфигурационный файл — это файл `guns-recoil-config.cfg`, который описывает параметры отдачи (`recoil`) и разброса (`spread`) для каждого оружия.

Формат поддерживает:

- **Секции** — блоки `[имя_секции]`, содержащие пары `ключ = значение`.
- **Наследование** — секция может наследовать значения от родительской секции (по имени до последней точки).
- **Комментарии** — строки, начинающиеся с `;` или `#`, а также пустые строки игнорируются.

---

## 2. Общий синтаксис

```
; комментарий
# тоже комментарий

[имя_секции]
ключ = значение
ключ = значение
```

### Правила

| Элемент | Описание |
|---|---|
| Секция | `[имя]` — имя обязательно, длина < 64 символов |
| Ключ | до `=` (пробелы обрезаются), длина < 64 символов |
| Значение | после `=`, длина < 64 символов |
| Комментарий | строка начинается с `;` или `#` |
| Пустая строка | игнорируется |
| Разделитель | только `=`, знак `:` не поддерживается |

> **Важно:** параметры вне секции (до первой `[...]`) вызывают ошибку загрузки.

---

## 3. Секции оружия

### 3.1. Именование

Имя секции должно содержать точку `.`. Это признак того, что секция относится к оружию (см. `IsWeaponNode` в `config_manager.c`).

Формат: `<категория>.<модель>`

Примеры:
- `pistol.p228`
- `rifle.ak-47`
- `sniper.awp`
- `shotgun.xm1014`
- `smg.mp5`
- `machinegun.m249`

### 3.2. Категории (`WeaponType`)

Определяются по префиксу имени (см. `WeaponInfo_GetType`):

| Префикс | Тип |
|---|---|
| `pistol.` | `WEAPON_TYPE_PISTOL` |
| `smg.` | `WEAPON_TYPE_SMG` |
| `rifle.` | `WEAPON_TYPE_RIFLE` |
| `shotgun.` | `WEAPON_TYPE_SHOTGUN` |
| `sniper.` | `WEAPON_TYPE_SNIPER` |
| `machinegun.` | `WEAPON_TYPE_MACHINEGUN` |
| прочее | `WEAPON_TYPE_UNKNOWN` |

> **Внимание:** в текущей реализации `WeaponInfo_GetType` распознаёт только `pistol.`, `rifle.`, `shotgun.`. Для `smg.`, `sniper.`, `machinegun.` возвращается `WEAPON_TYPE_UNKNOWN`. Это потенциальный баг — см. раздел 8.

### 3.3. Распознаваемые имена оружия (`WeaponId`)

| Имя секции | ID |
|---|---|
| `pistol.p228` | 1 |
| `sniper.scout` | 3 |
| `shotgun.xm1014` | 5 |
| `smg.mac10` | 7 |
| `rifle.aug` | 8 |
| `pistol.elite` | 10 |
| `pistol.fiveseven` | 11 |
| `smg.ump45` | 12 |
| `sniper.sg550` | 13 |
| `rifle.galil` | 14 |
| `rifle.famas` | 15 |
| `pistol.usp` | 16 |
| `pistol.glock18` | 17 |
| `sniper.awp` | 18 |
| `smg.mp5` | 19 |
| `machinegun.m249` | 20 |
| `shotgun.m3` | 21 |
| `rifle.m4a1` | 22 |
| `smg.tmp` | 23 |
| `sniper.g3sg1` | 24 |
| `rifle.sg552` | 25 |
| `pistol.deagle` | 26 |
| `rifle.ak-47` | 28 |
| `smg.p90` | 30 |

> Если секция похожа на оружие (содержит `.`), но имя не распознано — загрузка завершается ошибкой `Unknown weapon section`.

---

## 4. Ключи параметров

Все ключи относятся к текущей секции. Поддерживаются следующие:

### 4.1. Отдача (`RecoilParams` → `WeaponRecoil`)

| Ключ | Тип | Поле | Описание |
|---|---|---|---|
| `recoil.up_base` | float | `up_base` | Базовая вертикальная отдача |
| `recoil.lateral_base` | float | `lateral_base` | Базовая горизонтальная отдача |
| `recoil.up_modifier` | float | `up_modifier` | Модификатор вертикальной отдачи |
| `recoil.lateral_modifier` | float | `lateral_modifier` | Модификатор горизонтальной отдачи |
| `recoil.up_max` | float | `up_max` | Максимум вертикальной отдачи |
| `recoil.lateral_max` | float | `lateral_max` | Максимум горизонтальной отдачи |
| `recoil.direction_change` | int | `direction_change` | Смена направления (0/1) |

### 4.2. Разброс (`SpreadParams` → `WeaponSpread`)

| Ключ | Тип | Поле | Описание |
|---|---|---|---|
| `spread` | float | `spread` | Значение разброса |

---

## 5. Наследование секций

### 5.1. Корневая секция

`[default]` является корневой секцией конфигурации.

Все категории и оружейные секции, для которых требуется наследование, в конечном итоге должны иметь цепочку до `[default]`.

Например:

rifle.ak-47 → rifle → default

Если необходимая родительская секция отсутствует, загрузка завершается ошибкой.

### 5.2. Слияние

`MergeNode` копирует поля из дочерней секции поверх родительской **только если** у дочерней поле помечено `set = 1` (т.е. было явно задано в файле).

Это позволяет создавать иерархии:

```
[default]
recoil.up_base = 1.0
recoil.lateral_base = 0.5
spread = 0.01

[rifle]
recoil.up_base = 2.0

[rifle.ak-47]
recoil.up_max = 10.0
```

Для `rifle.ak-47` итог:
- `up_base = 2.0` (из `rifle`)
- `lateral_base = 0.5` (из `default`)
- `spread = 0.01` (из `default`)
- `up_max = 10.0` (своё)

> Наследование работает по **полной цепочке**, рекурсивно (`ResolveNode` вызывает сам себя).

### 5.3. Ограничения наследования

- Имя родителя должно быть ≤ 63 символов.
- Циклические зависимости не обнаруживаются — при ошибке в иерархии возможна бесконечная рекурсия (см. раздел 8).

---

## 6. Пример полного файла

```ini
; ============================================
; Guns Recoil - Settings Config
; ============================================

[default]
recoil.up_base = 1.0
recoil.lateral_base = 0.5
recoil.up_modifier = 1.0
recoil.lateral_modifier = 1.0
recoil.up_max = 10.0
recoil.lateral_max = 5.0
recoil.direction_change = 0
spread = 0.01

; --- Пистолеты ---
[pistol]
recoil.up_base = 1.2
recoil.lateral_base = 0.6
spread = 0.02

[pistol.p228]
recoil.up_max = 6.0
spread = 0.015

[pistol.deagle]
recoil.up_base = 3.0
recoil.lateral_base = 1.5
recoil.up_max = 15.0
spread = 0.05

; --- Винтовки ---
[rifle]
recoil.up_base = 2.0
recoil.lateral_base = 0.8
spread = 0.03

[rifle.ak-47]
recoil.up_modifier = 1.5
recoil.up_max = 12.0

[rifle.m4a1]
recoil.up_modifier = 1.2
recoil.lateral_modifier = 0.9
recoil.up_max = 10.0

; --- Снайперские ---
[sniper]
recoil.up_base = 5.0
recoil.lateral_base = 2.0
spread = 0.001

[sniper.awp]
recoil.up_max = 20.0
```

---

## 7. Обработка ошибок

| Ситуация | Поведение |
|---|---|
| Не удалось открыть файл | `Failed to open config: <path>` |
| Пустая или невалидная секция | `Invalid section at line N` |
| Невалидная строка `key = value` | `Invalid config entry at line N: ...` |
| Параметр вне секции | `Config entry outside of section at line N` |
| Не удалось создать узел | `Failed to create config node for section '...' at line N` |
| Невалидный ключ/значение | `Invalid key/value at line N: key = value` |
| Неизвестное оружие | `Unknown weapon section: '...'` |
| Родитель не найден | `Parent node '...' not found for '...'` |
| Не удалось разрешить узел | `Failed to resolve node '...'` |

При любой ошибке `ConfigManager_Load` возвращает `0`.

---

## 8. Известные ограничения и потенциальные проблемы

1. **`WeaponInfo_GetType` неполный** — не распознаёт `smg.`, `sniper.`, `machinegun.`. Возвращает `WEAPON_TYPE_UNKNOWN`.
2. **`enabled` и `type` нельзя задать через конфиг**
3. **Размер строки — 128 байт.** Строки длиннее буфера не поддерживаются и могут быть обработаны некорректно.

---

## 9. API

### `ConfigManager_Load`
```c
int ConfigManager_Load(ConfigManager* manager, const char* path);
```
Загружает конфиг из файла. Возвращает `1` при успехе, `0` при ошибке.

### `ConfigManager_GetWeaponParams`
```c
const WeaponParams* ConfigManager_GetWeaponParams(
    const ConfigManager* manager,
    int weapon_id
);
```
Возвращает указатель на параметры оружия по ID или `NULL`, если ID вне диапазона `[0, WEAPON_MAX_ID)`.

### `WeaponInfo_GetId` / `WeaponInfo_GetType`
```c
int WeaponInfo_GetId(const char* name);
WeaponType WeaponInfo_GetType(const char* name);
```
Вспомогательные функции сопоставления имени секции с ID и типом.

---

## 10. Быстрый старт

1. Добавьте секцию `[default]` с базовыми значениями.
2. Добавьте секции `[<категория>]` для каждой категории оружия.
3. Добавьте секции `[<категория>.<модель>]` для конкретных стволов.
