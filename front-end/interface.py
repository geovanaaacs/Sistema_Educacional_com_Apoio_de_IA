import customtkinter as ctk
import tkinter.messagebox as msgbox
from pathlib import Path

icon = Path(__file__).parent / "source" / "icon.ico"

def set_up_interface():
    interface = ctk.CTk()
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("blue")
    interface.geometry("900x600")
    # faz aparecer na frente de outras janelas
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
    
    button_login = ctk.CTkButton(master=frame_login, text="Entrar", width=200)
    button_login.pack(pady=10)
    
    button_not_registered = ctk.CTkButton(master=frame_login, text="Não tenho cadastro",command=msg_not_registered, font=ctk.CTkFont(size=12), fg_color="transparent", hover_color="gray25")
    button_not_registered.pack(pady=0)
        
def show_password_button(checkbox, password_entry):
    if checkbox.get() == 1:
        password_entry.configure(show="")
    else:
        password_entry.configure(show="*")

def msg_not_registered():
    msgbox.showinfo(title="Cadastro Pendente", message="Para fazer seu cadastro, por favor, entre em contato com a secretaria da escola.")
    
def verify_login_data(email, password): # dar continuirdade depois
    try:
        with open("data/login_data.txt", "r") as file:
            for line in file:
                stored_email, stored_password = line.strip().split(",")
                if email == stored_email and password == stored_password:
                    return True
                
    except:
        return False

def main():
    interface = set_up_interface()
    homepage(interface)
    
    interface.mainloop()
    
    
if __name__ == "__main__":
    main()