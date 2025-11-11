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
        msgbox.showerror("Erro", f"Ocorreu um problema ao ler os dados: {e}")
        return None

def login_success(interface, user_data):
    # Fecha a janela anterior e cria nova interface
    for widget in interface.winfo_children():
        widget.destroy()  # Removido o "4"
    
    interface.title("Painel do Usuário")
    interface.geometry("1000x700")
    
    notas = []
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
                
                for n in notas:
                    if "Nota" in n:
                        try:
                            n["Nota"] = f"{float(n['Nota']):.2f}"
                        except ValueError:
                            pass
                        
    except FileNotFoundError:
        msgbox.showwarning(f"⚠️ Arquivo '{notes_data_path}' não encontrado. Exibindo painel vazio.")
            
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

        entry_busca = ctk.CTkEntry(busca_frame, placeholder_text="Buscar por nome ou turma...", width=250)
        entry_busca.pack(side="left", padx=5)

        botao_busca = ctk.CTkButton(busca_frame, text="Filtrar", width=100)
        botao_busca.pack(side="left", padx=5)

    tabela_notas = ttk.Treeview(frame_notas, columns=("Aluno", "Turma", "Disciplina", "Nota"), show="headings")
    
    for n in notas:
        tabela_notas.insert("", "end", values=(n["Aluno"], n["Turma"], n["Disciplina"], n["Nota"]))
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
        msgbox.showwarning(f"⚠️ Arquivo '{activities_data_path}' não encontrado. Exibindo painel vazio.")
        
    except Exception as e:
        msgbox.showwarning(f"⚠️ Erro ao ler atividades: {e}")
        
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
