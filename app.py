from flask import Flask, render_template, redirect, url_for, flash
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired
from flask_login import LoginManager, UserMixin, login_user, logout_user, login_required
import pandas as pd

app = Flask(__name__)
app.secret_key = 'secret'
login_manager = LoginManager()
login_manager.init_app(app)

# Dummy user data
users = {'admin': 'password'}

class User(UserMixin):
    def __init__(self, username):
        self.username = username

    def get_id(self):
        return self.username

@login_manager.user_loader
def load_user(user_id):
    return User(user_id)

class LoginForm(FlaskForm):
    username = StringField('Username', validators=[DataRequired()])
    password = PasswordField('Password', validators=[DataRequired()])
    submit = SubmitField('Login')

@app.route('/')
def default():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if form.validate_on_submit():
        username = form.username.data
        password = form.password.data
        if username in users and users[username] == password:
            user = User(username)
            login_user(user)
            flash('Login Successful!', 'success')
            return redirect(url_for('dashboard'))
        else:
            flash('Login Unsuccessful. Please check username and password', 'danger')
    return render_template('login.html', form=form)

@app.route('/logout')
@login_required
def logout():
    logout_user()
    flash('You have been logged out.', 'info')
    return redirect(url_for('login'))

@app.route('/dashboard')
@login_required
def dashboard():
    df = pd.read_csv('static/data/data_padi.csv')

    bar_data = df['Produksi'].tolist()  
    line_data = df['Luas_panen'].tolist()  
    pie_data = [{'name': row['Provinsi'], 'y': row['Produksi']} for index, row in df.iterrows()]  
    area_data = df['Curah_hujan'].tolist()  
    provinsi =  df['Provinsi'].tolist()


    dataset = df.to_dict(orient='records') 

    return render_template('dashboard.html', bar_data=bar_data, line_data=line_data, pie_data=pie_data, area_data=area_data,  provinsi=provinsi, dataset=dataset)


if __name__ == '__main__':
    app.run(debug=True)
