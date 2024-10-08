from flask import Flask, render_template, redirect, url_for, flash
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField, DateField
from wtforms.validators import DataRequired
from flask_login import LoginManager, UserMixin, login_user, logout_user, login_required
import pandas as pd
from datetime import datetime

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

class DateFilterForm(FlaskForm):
    date = DateField('Tanggal', format='%Y-%m-%d', validators=[DataRequired()])
    submit = SubmitField('Filter')

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

@app.route('/dashboard', methods=['GET', 'POST'])
@login_required
def dashboard():
    df = pd.read_csv('static/data/losses.csv')

    df['DATE_FOSS_ANALYSIS'] = pd.to_datetime(df['DATE_FOSS_ANALYSIS'], format='%d/%m/%Y', errors='coerce')
    latest_date = df['DATE_FOSS_ANALYSIS'].max()
    
    form = DateFilterForm()
    if form.date.data is None:
        form.date.data = latest_date.date()

    if form.validate_on_submit():
        selected_date = form.date.data
        
        filtered_df = df[df['DATE_FOSS_ANALYSIS'].dt.date == selected_date]

        if filtered_df.empty:
            flash('No data found for the selected date', 'warning')
        else:
            df = filtered_df

    df['DATE_FOSS_ANALYSIS'] = df['DATE_FOSS_ANALYSIS'].dt.strftime('%d/%m/%Y')

    pks_code = df['PKS_CODE'].tolist()
    pks_name = df['PKS_NAME'].tolist()
    norma_ap = df['NORMA_AMPAS_PRESS'].tolist()
    losis_ap = df['LOSIS_%_AMPAS_PRESS'].tolist()
    norma_bj = df['NORMA_BIJI'].tolist()
    losis_bj = df['LOSIS_%_BIJI'].tolist()
    norma_tk = df['NORMA_TANDAN_KOSONG'].tolist()
    losis_tk = df['LOSIS_%_TANDAN_KOSONG'].tolist()
    norma_da = df['NORMA_DRAB_AKHIR'].tolist()
    losis_da = df['LOSIS_%_DRAB_AKHIR'].tolist()
    norma_sd = df['NORMA_SOLID_DECANTER'].tolist()
    losis_sd = df['LOSIS_%_SOLID_DECANTER'].tolist()
    norma_pks = df['NORMA_PKS_PER_DATE'].tolist()
    losis_pks = df['LOSIS_PKS'].tolist()

    dataset = df.to_dict(orient='records')
    columns = df.columns.tolist()

    return render_template('dashboard.html', form=form, pks_code=pks_code, pks_name=pks_name, norma_ap=norma_ap, losis_ap=losis_ap, 
                           norma_bj=norma_bj, losis_bj=losis_bj, norma_tk=norma_tk, losis_tk=losis_tk, norma_da=norma_da, losis_da=losis_da, 
                           norma_sd=norma_sd, losis_sd=losis_sd, norma_pks=norma_pks, losis_pks=losis_pks, dataset=dataset, columns=columns)

if __name__ == '__main__':
    app.run(debug=True)
