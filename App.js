import { StatusBar } from 'expo-status-bar';
import { ScrollView, StyleSheet, Text, View, Switch, Touchable, TouchableOpacity } from 'react-native';
import React, {useState} from 'react';
import {MaterialIcons} from '@expo/vector-icons'

import axios from 'axios';

export default function App() {

  // Definindo as constantes para alterar o botao de LED vermelho (Red)
  const [isEnableR, setIsEnableR] = useState(false) 
  
  // Definindo o coportamento de quando o botao for tocado no objeto switch
  const isSwitchR = () => {
    setIsEnableR(previousState => !previousState)
  }
  
  // Variavel que define o comportamento do LED ao ser pressionado via HTTP
  const ledR = () => {
    if (isEnableR == false){
      axios.get('http://192.168.1.29/ledR/on').then(response =>{
        console.log('LED vermelha ligada :D')
      })
    }else{
      axios.get('http://192.168.1.29/ledR/off').then(response => {
        console.log('LED vermelha desligada :/')
      })
    }
  }

  // *************************************************** //
  
  // Definindo as constantes para alterar o botao de LED verde (Green)
  const [isEnableG, setIsEnableG] = useState(false)

  // Definindo o coportamento de quando o botao for tocado no objeto switch
  const isSwitchG = () => {
    setIsEnableG(previousState => !previousState)
  }

  // Variavel que define o comportamento do LED ao ser pressionado via HTTP
  const ledG = () => {
    if (isEnableG == false){
      axios.get('http://192.168.1.29/ledG/on').then(response =>{
        console.log('LED verde ligada :D')
      })
    }else{
      axios.get('http://192.168.1.29/ledG/off').then(response => {
        console.log('LED verde desligada :/')
      })
    }
  }
  
  // **************************************************** //

  // Definindo as variaveis para recuperar o valor de humidade e temperatura, inicializando-as
  const [humid, setHumid] = useState('--') 
  const [temp, setTemp] = useState('.')

  const getTemperature = () => {
    axios.get('http://192.168.1.29/sensor/temp').then(response => {
      setTemp(temperature => response.data)
      console.log(`Temperatura atualizada ${temp} C`)
    })
  }

  const getUmidity = () => {
    axios.get('http://192.168.1.29/sensor/humi').then(response => {
      setHumid(humidity => response.data)
      console.log(`Humidade atualizada ${humid} %`)
    })
  }

  return (
  <> 
  {/* tag vazia para remover possiveis problemas*/}
  <StatusBar/> 
  {/* barra para carregamento no app */}
    <ScrollView>
      <View style={styles.container}>
        {/* Titulo Superior */}
        <Text style={{alignSelf:'center',marginBottom:20,color:'white'}}>Casa Cilene Automation</Text>
        
        {/* Dados dos LEDS */}

          <Text style={styles.title}>LED Vermelho</Text>
          <View style={styles.status}>
            <Text style={isEnableR ? styles.ON : styles.OFF}> {isEnableR ? 'ON' : 'OFF'} </Text>
            <Switch
              onValueChange = {isSwitchR}
              value = {isEnableR}
              onChange={ledR}
            />
          </View>
          <Text style={styles.title}>LED Verde</Text>
          <View style={styles.status}>
            <Text style={isEnableG ? styles.ON : styles.OFF}> {isEnableG ? 'ON' : 'OFF'} </Text>
            <Switch
              onValueChange = {isSwitchG}
              value = {isEnableG}
              onChange={ledG}
            />
          </View>

        {/* Dados de Monitoramento */}

          <View style={styles.status}>
            <Text style={styles.title}>Temperatura: </Text>
            <Text style={styles.subtitle}> <Text style={styles.value}>{temp}</Text> C</Text>
            <TouchableOpacity onPress={getTemperature}>
              <MaterialIcons name='sync' size={45} color={'#fff'}/>
            </TouchableOpacity>
          </View>
          <View style={styles.status}>
            <Text style={styles.title}>Umidade:</Text>
            <Text style={styles.subtitle}> <Text style={styles.value}>{humid}</Text> %</Text>
            <TouchableOpacity onPress={getUmidity}>
              <MaterialIcons name='sync' size={45} color={'#fff'}/>
            </TouchableOpacity>
          </View>      

        <StatusBar style="auto" />
      </View>
    </ScrollView>
    <Text style={{alignSelf:'center'}}>1.0.0 version</Text>
  </>
);
}

// Configuracao Front-End CSS

const styles = StyleSheet.create({
container: {
  flex: 1,
  backgroundColor: '#333', // cinza escuro
  alignItems: 'center',
  justifyContent: 'center',
  marginTop:150
},
title:{
  fontSize: 30,
  color: '#ff5'
},
subtitle:{
  alignSelf:'center',
  fontWeight:'bold',
  textAlign:'justify',
  fontSize: 35,
  color: "#ddd" // cinza claro
},
ON:{
  color:'yellowgreen'
},
OFF:{
  color:'red'
},
status:{
  flexDirection:'row',
  justifyContent:'space-around'
},
value:{
  color:'#eee',
  fontSize:38
}
});
