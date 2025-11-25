import customtkinter as ctk
import tkinter.messagebox as msgbox
from pathlib import Path
import tkinter.ttk as ttk

script_dir = Path(__file__).parent
project_root = script_dir.parent
user_data_path = project_root / "back-end" / "dados_usuarios.txt"
notes_data_path = project_root / "back-end" / "notas_registradas.txt"
activities_data_path = project_root / "back-end" / "dados_atividades.txt"
icon = script_dir / "source" / "icon.ico"

with open(user_data_path, "r", encoding="utf-8") as file:  # Padronizei para utf-8
    conteudo = file.read()

def set_up_interface():
    interface = ctk.CTk()
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("blue")
    interface.geometry("900x600")
    interface.attributes("-topmost", True)
    interface.title("Sistema Educacional com Apoio de IA")
    interface.iconbitmap(icon)
    return interface

def homepage(interface):
    frame_login = ctk.CTkFrame(interface, fg_color="transparent")
    frame_login.pack(expand=True)
    
    tittle = ctk.CTkLabel(master=frame_login, text="Bem vindo ao Sistema Educacional\n com Apoio de IA", font=ctk.CTkFont(size=15, weight="bold"))
    tittle.pack(pady=20)
    
    text_login_email = ctk.CTkLabel(master=frame_login, text="Email:", font=ctk.CTkFont(size=12))
    text_login_email.pack(pady=(0, 2), padx=5, anchor="w")
    
    login_email = ctk.CTkEntry(master=frame_login, placeholder_text="Digite seu email:", width=300)
    login_email.pack(pady=(0, 10))
    
    text_login_password = ctk.CTkLabel(master=frame_login, text="Senha:", font=ctk.CTkFont(size=12))
    text_login_password.pack(pady=(0, 2), padx=5, anchor="w")
    
    login_password = ctk.CTkEntry(master=frame_login, placeholder_text="Digite sua senha:", width=300, show="*")
    login_password.pack(pady=(0, 10))
    
    checkbox_show_password = ctk.CTkCheckBox(master=frame_login, text="Mostrar senha", checkbox_width=18, checkbox_height=18, command=lambda: show_password_button(checkbox_show_password, login_password))
    checkbox_show_password.pack(pady=(0, 10), padx=5, anchor="w")

    def handle_login():
        email = login_email.get().strip()
        password = login_password.get().strip()
        user_data = verify_login_data(email, password)
        if user_data:
            frame_login.pack_forget() 
            login_success(interface, user_data)
        else:
            msgbox.showerror("Login Falhou", "Email ou senha incorretos.")

    button_login = ctk.CTkButton(master=frame_login, text="Entrar", width=200, command=handle_login) 
    button_login.pack(pady=10)
    
    button_not_registered = ctk.CTkButton(master=frame_login, text="Não tenho cadastro", command=msg_not_registered, font=ctk.CTkFont(size=12), fg_color="transparent", hover_color="gray25")
    button_not_registered.pack(pady=0)

def show_password_button(checkbox, password_entry):
    if checkbox.get() == 1:
        password_entry.configure(show="")
    else:
        password_entry.configure(show="*")

def msg_not_registered():
    msgbox.showinfo(title="Cadastro Pendente", message="Para fazer seu cadastro, por favor, entre em contato com a secretaria da escola.")

def verify_login_data(email_attempt, password_attempt): 
    try:
        with open(user_data_path, "r", encoding='utf-8') as file:
            all_content = file.read().strip()
            if all_content:
                user_records = all_content.split('\n\n')
            
            for record_str in user_records:
                user_data = {}
                lines = record_str.strip().split('\n')
                
                for line in lines:
                    if ": " in line:
                        key, value = line.split(": ", 1)
                        user_data[key.strip()] = value.strip()

                if (user_data.get('Email') == email_attempt and 
                    user_data.get('Senha') == password_attempt):
                    return user_data

    except FileNotFoundError:
        msgbox.showerror("Erro", f"Arquivo '{user_data_path}' não encontrado.")
        return None
    except Exception as e:
        msgbox.showerror("Erro", f"Erro ao verificar login: {str(e)}")
        return None

def login_success(interface, user_data):
    # Fecha a janela anterior e cria nova interface
    for widget in interface.winfo_children():
        widget.destroy()  # Removido o "4"
    
    interface.title("Painel do Usuário")
    interface.geometry("1000x700")
    
    notas = []
    nome_aluno = user_data.get('Nome', '')
    try:
        with open(notes_data_path, "r", encoding="utf-8") as file:
                dados = {}
                for linha in file:
                    linha = linha.strip()
                    if not linha:
                        if dados:
                            notas.append(dados)
                            dados = {}
                        continue
                    if ":" in linha:
                        chave, valor = linha.split(":", 1)
                        dados[chave.strip()] = valor.strip()
                if dados:
                    notas.append(dados)
                
                # Filtrar notas: alunos veem apenas suas notas, professores veem todas
                if user_data.get('Cargo') == 'Aluno':
                    notas = [n for n in notas if n.get('Aluno') == nome_aluno]
                
                for n in notas:
                    if "Nota" in n:
                        try:
                            valor = n["Nota"].replace(",", ".")
                            try:
                                n["Nota"] = f"{float(valor):.1f}"
                            except:
                                pass

                        except ValueError:
                            pass
                        
    except FileNotFoundError:
        msgbox.showwarning("Aviso", "Arquivo de notas nao encontrado. Exibindo painel vazio.")
    except Exception as e:
        msgbox.showerror("Erro", f"Erro ao ler notas: {str(e)}")
            
    # Frame principal
    main_frame = ctk.CTkFrame(interface)
    main_frame.pack(fill="both", expand=True, padx=20, pady=20)
    label = ctk.CTkLabel(main_frame, text=f"Olá, {user_data.get('Nome', 'Usuário')}!\nBem-vindo ao painel.", font=ctk.CTkFont(size=16, weight="bold"))
    label.pack(pady=20)

    container = ctk.CTkFrame(main_frame, fg_color="transparent")
    container.pack(fill="both", expand=True)
    
    frame_notas = ctk.CTkFrame(container, corner_radius=15)
    frame_notas.grid(row=0, column=0, sticky="nsew", padx=10, pady=10)
   
    titulo_notas = ctk.CTkLabel(frame_notas, text="📊 Dashboard de Notas", font=ctk.CTkFont(size=16, weight="bold"))
    titulo_notas.pack(pady=10)
    
    if user_data.get('Cargo') != 'Aluno':
        busca_frame = ctk.CTkFrame(frame_notas, fg_color="transparent")
        busca_frame.pack(pady=5)

        ctk.CTkLabel(busca_frame, text="Filtrar por:", font=ctk.CTkFont(size=11)).pack(side="left", padx=5)
        
        entry_turma = ctk.CTkEntry(busca_frame, placeholder_text="Turma", width=80)
        entry_turma.pack(side="left", padx=5)

        entry_disciplina = ctk.CTkEntry(busca_frame, placeholder_text="Disciplina", width=100)
        entry_disciplina.pack(side="left", padx=5)

        def aplicar_filtro():
            turma_filtro = entry_turma.get().strip().lower()
            disciplina_filtro = entry_disciplina.get().strip().lower()
            
            # Limpar tabela
            for item in tabela_notas.get_children():
                tabela_notas.delete(item)
            
            # Recarregar com filtro
            for n in notas:
                turma_nota = n.get('Turma', '').lower()
                disciplina_nota = n.get('Disciplina', '').lower()
                
                # Professores só veem notas da sua turma e disciplina
                prof_turma = user_data.get('Turma', '').lower()
                prof_disciplina = user_data.get('Disciplina', '').lower()
                
                turma_ok = not turma_filtro or turma_nota == turma_filtro
                disciplina_ok = not disciplina_filtro or disciplina_nota == disciplina_filtro
                acesso_ok = turma_nota == prof_turma and disciplina_nota == prof_disciplina
                
                if turma_ok and disciplina_ok and acesso_ok:
                    tabela_notas.insert("", "end", values=(n.get("Aluno", ""), n.get("Turma", ""), n.get("Disciplina", ""), n.get("Nota", "")))

        botao_busca = ctk.CTkButton(busca_frame, text="Filtrar", width=80, command=aplicar_filtro)
        botao_busca.pack(side="left", padx=5)

    tabela_notas = ttk.Treeview(frame_notas, columns=("Aluno", "Turma", "Disciplina", "Nota"), show="headings")
    
    # Inserir notas respeitando filtro de professor
    prof_turma = user_data.get('Turma', '').lower() if user_data.get('Cargo') != 'Aluno' else None
    prof_disciplina = user_data.get('Disciplina', '').lower() if user_data.get('Cargo') != 'Aluno' else None
    
    for n in notas:
        # Se for professor, verificar se a nota é da sua turma/disciplina
        if user_data.get('Cargo') != 'Aluno':
            disciplina_nota = n.get('Disciplina', '').strip().lower()
            prof_disciplina = user_data.get('Disciplina', '').strip().lower()
            
            # Mostrar apenas notas que correspondem À DISCIPLINA do professor (em qualquer turma)
            if disciplina_nota != prof_disciplina:
                continue
            
        tabela_notas.insert("", "end", values=(n.get("Aluno", ""), n.get("Turma", ""), n.get("Disciplina", ""), n.get("Nota", "")))
    tabela_notas.pack(fill="both", expand=True, padx=10, pady=10)         
    
    for col in ("Aluno", "Turma", "Disciplina", "Nota"):
        tabela_notas.heading(col, text=col)
        tabela_notas.column(col, width=120)
    tabela_notas.pack(fill="both", expand=True, padx=10, pady=10)
    
    if not notas:
        ctk.CTkLabel(frame_notas, text="Nenhuma nota registrada no momento.",
                     font=ctk.CTkFont(size=12, slant="italic"), text_color="gray").pack(pady=20)

    # Frame de Atividades
    frame_atividades = ctk.CTkFrame(container, corner_radius=15)
    frame_atividades.grid(row=0, column=1, sticky="nsew", padx=10, pady=10)

    titulo_ativ = ctk.CTkLabel(frame_atividades, text="📝 Atividades", font=ctk.CTkFont(size=16, weight="bold"))
    titulo_ativ.pack(pady=10)

    atividades = []
    try:
        with open(activities_data_path, "r", encoding="utf-8") as file:
            for linha in file:
                partes = linha.strip().split(",")
                if len(partes) >= 3: 
                    atividades.append({
                        "Atividade": partes[0],
                        "Turma": partes[1],
                        "Descricao": partes[2]
                    })
                    
    except FileNotFoundError:
        msgbox.showwarning("Aviso", "Arquivo de atividades nao encontrado. Exibindo painel vazio.")
        
    except Exception as e:
        msgbox.showerror("Erro", f"Erro ao ler atividades: {str(e)}")
        
    if atividades:
        for a in atividades:
            item_frame = ctk.CTkFrame(frame_atividades, fg_color="gray20")
            item_frame.pack(fill="x", pady=5, padx=10)
            ctk.CTkLabel(item_frame, text=f"{a['Atividade']} ({a['Turma']})", font=ctk.CTkFont(size=13, weight="bold")).pack(anchor="w", padx=10, pady=(5, 0))
            ctk.CTkLabel(item_frame, text=a["Descricao"], font=ctk.CTkFont(size=12), wraplength=300).pack(anchor="w", padx=10, pady=(0, 5))
    else:
        ctk.CTkLabel(frame_atividades, text="Nenhuma atividade disponível no momento.",
                     font=ctk.CTkFont(size=12, slant="italic"), text_color="gray").pack(pady=20)

    container.columnconfigure(0, weight=1)
    container.columnconfigure(1, weight=1)
    container.rowconfigure(0, weight=1)

    # Removido interface.mainloop() daqui

def main():
    interface = set_up_interface()
    homepage(interface)
    interface.mainloop()
    
if __name__ == "__main__":
    main()
