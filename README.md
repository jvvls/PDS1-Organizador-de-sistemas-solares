# 🌌 Sistema de Organização de Sistemas Solares

Projeto desenvolvido na disciplina **Programação e Desenvolvimento de Software I** (1º período), como exercício de manipulação de **structs em C**, **alocação dinâmica** e **algoritmos de ordenação**.

---

## 📖 Descrição

O programa simula o cadastro e organização de **sistemas solares**.  
Cada sistema contém:

- **Sol** (com raio e tempo associado)  
- **Planetas** (cada um com raio e quantidade de luas)  
- **Luas** (cada uma com raio próprio)  

Os sistemas são lidos da entrada padrão, armazenados dinamicamente e depois **ordenados** de acordo com critérios de comparação definidos pelo algoritmo `BrometoSort` (uma adaptação de *merge sort*).

---

## 🛠️ Funcionalidades

- Cadastro dinâmico de múltiplos sistemas solares.  
- Estruturas hierárquicas com `struct`:  
  - `Lua`  
  - `Planeta`  
  - `Sistema_Solar`  
- Ordenação personalizada dos sistemas:  
  - Primeiro pelo **raio do Sol**;  
  - Em caso de empate, pela **quantidade de planetas**;  
  - Em seguida, pelo **maior planeta**;  
  - Depois, pelo **maior lua**;  
  - Critérios sucessivos até considerar o **tempo** do sistema.  
- Impressão da lista ordenada de sistemas pelo **nome**.  
- Liberação correta da memória alocada (sem *memory leaks*).

---

## 📂 Estrutura do Código

- `struct Lua` → raio e nome.  
- `struct Planeta` → raio, nome, número de luas e ponteiro para array dinâmico de luas.  
- `struct Sistema_Solar` → raio do Sol, nome, tempo, número de planetas e ponteiro para array dinâmico de planetas.  

Principais funções:
- `LeLua` → Lê as luas de um planeta.  
- `LePlaneta` → Lê os planetas de um sistema.  
- `cadastro_sistemas` → Lê todos os sistemas solares.  
- `Comparador_Legal` → Define a prioridade entre dois sistemas.  
- `BrometoSort` → Ordena os sistemas com base no comparador.  
- `ritacao` → Mescla os subarrays no processo de ordenação.  
- `ListaOrdenada` → Exibe o resultado final da ordenação.  
- `liberar_memoria` → Libera toda a memória alocada.  

---

## ▶️ Como Compilar e Executar

No Linux:

```bash
gcc sistemas_solares.c -o sistemas_solares
./sistemas_solares < entrada.txt
