import flet as ft

def main(page):
    
    title = ft.Text("Chat")
    
    popup_title = ft.Text("Login")
    name_field = ft.TextField(label="Type your name")
    
    chat = ft.Column()
    text_field = ft.TextField(label="Type your text")
    
    def conection(message):
        chat_text = ft.Text(message)
        chat.controls.append(chat_text)
        page.update()
        
    page.pubsub.subscribe(conection)
    
    def sendMessage(event):
        message = f"{name_field.value}: {text_field.value}"
        page.pubsub.send_all(message)
        text_field.value = ""
        page.update()
        
    
    text_field = ft.TextField(label="Type your text", on_submit=sendMessage)
        
    send_button = ft.ElevatedButton("Send", on_click=sendMessage)
    
    message_row = ft.Row([text_field, send_button])
    
    def joinChat(event):
        page.remove(title)
        page.remove(enter_button)
        popup.open = False
        page.add(chat)
        page.add(message_row)
        message = f"{name_field.value} entrou no chat"
        page.pubsub.send_all(message)
        page.update()
        
    
    join_chat_button = ft.ElevatedButton("Join Chat", on_click=joinChat)
    popup = ft.AlertDialog(
        title=popup_title,
        content=name_field,
        actions=[join_chat_button])
    
    def loginChat(event):
        page.dialog = popup
        popup.open = True
        page.update()
    
    enter_button = ft.ElevatedButton("Login", on_click=loginChat)
    page.add(title)
    page.add(enter_button)
    
    

# ft.app(main) #pra rodar o sistema
ft.app(target=main, view=ft.WEB_BROWSER, port=8000)
