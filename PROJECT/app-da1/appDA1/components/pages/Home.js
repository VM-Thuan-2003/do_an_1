import React, { useEffect, useState } from "react";
import { View, Text, StyleSheet, TextInput, Button} from "react-native";
import { db } from "../configs/firebaseConfig";
import { onValue, ref, set } from "firebase/database";

const Home = (props) => {
  const [hh,sethh] = useState(0)
  const [pp,setpp] = useState(0)
  const [ss,setss] = useState(0)
  const [tempLimit, setTempLimit] = useState(0)
  const [tempReal, setTempReal] = useState(0)
  const [valuehh, onChangeTexthh] = useState(11);
  const [valuepp, onChangeTextpp] = useState(11);
  const [valuess, onChangeTextss] = useState(11);
  const [valuetempLimit, onChangeTexttemp] = useState(25);

  var set_time_fish = () => {
    console.log("set_time_fish",valuehh, valuepp, valuess)
    try {
      set(ref(db, "set/alarm/eat"), {
        "hh":valuehh,
        "pp":valuepp,
        "ss":valuess
      });
      console.log("Data written successfully!");
    } catch (error) {
      console.error("Error writing data:", error);
    }
  }

  var set_temp_fish = () => {
    console.log("set_temp_fish",valuetempLimit)
    try {
      set(ref(db, "set/alarm/eat"), valuetempLimit);
      console.log("Data written successfully!");
    } catch (error) {
      console.error("Error writing data:", error);
    }
  }

  var control_eat_fish = () => {
    console.log("control_eat_fish")
    try {
      set(ref(db, "control/servo/eat"), 1);
      console.log("Data written successfully!");
    } catch (error) {
      console.error("Error writing data:", error);
    }
  }

  useEffect(() => {
    const intervalId = setInterval(() => {
      const data = ref(db, "data");
      onValue(data, (snapshot) => {
        const data = snapshot.val();
        sethh(data["alarm"]["eat"]["hh"])
        setpp(data["alarm"]["eat"]["pp"])
        setss(data["alarm"]["eat"]["ss"])

        setTempLimit(data["temperature"]["limit"])
        setTempReal(data["temperature"]["realtime"])
        console.log(data)
      });
    }, 10000);
    return () => clearInterval(intervalId);
  }, []);

  const styles = StyleSheet.create({
    home: {
      flex: 1,
      justifyContent: 'center',
      alignItems:'center',
      width: props.Dimensions.width
    },
  });

  return (
    <View style={styles.home}>
      <View>
        <Text style={{display:"flex","justifyContent":"center", fontSize: 18}}>
          Thời gian cho cá ăn
        </Text>
        <Text style={{display:"flex","justifyContent":"center"}}>
          {hh} - {pp} - {ss}
        </Text>
        <Text style={{display:"flex","justifyContent":"center", fontSize: 18}}>
          Thiết lập thời gian cho cá ăn
        </Text>
        <View style={{display:"flex","flexDirection":"row", "justifyContent":"center"}}>
          <View style={{display:"flex","flexDirection":"row"}}>
            <Text>
              giờ: 
            </Text>
            <TextInput
              maxLength={2}
              onChangeText={text => onChangeTexthh(text)}
              value={valuehh}
              style={{width:20}}
            />
          </View>
          <View style={{display:"flex","flexDirection":"row"}}>
            <Text>
              phút: 
            </Text>
            <TextInput
              maxLength={2}
              onChangeText={text => onChangeTextpp(text)}
              value={valuepp}
              style={{width:20}}
            />
          </View>
          <View style={{display:"flex","flexDirection":"row"}}>
            <Text>
              giây: 
            </Text>
            <TextInput
              maxLength={2}
              onChangeText={text => onChangeTextss(text)}
              value={valuess}
              style={{width:20}}
            />
          </View>
        </View>
        <View style={{paddingTop:10}}>
          <Button title="Thiết lập thời gian" onPress={set_time_fish} />
        </View>
      </View>
      <View style={{paddingTop:10}}>
        <Text style={{display:"flex","justifyContent":"center", fontSize: 18}}>
          Nhiệt độ hồ cá
        </Text>
        <Text style={{display:"flex","justifyContent":"center"}}>
          {tempReal} (oC)
        </Text>
      </View>
      <View style={{paddingTop:10}}>
        <Text style={{display:"flex","justifyContent":"center", fontSize: 18}}>
          Nhiệt độ giới hạn
        </Text>
        <Text style={{display:"flex","justifyContent":"center"}}>
          {tempLimit} (oC)
        </Text>
      </View>
      <View style={{paddingTop:10}}>
        <Text style={{display:"flex","justifyContent":"center", fontSize: 18}}>
          Cài nhiệt độ giới hạn
        </Text>
        <View style={{display:"flex","flexDirection":"row", "justifyContent":"center"}}>
          <TextInput
            maxLength={2}
            onChangeText={text => onChangeTexttemp(text)}
            value={valuetempLimit}
            style={{width:20}}
          />
          <Text>
            (oC)
          </Text>
        </View>
        <View style={{paddingTop:10}}>
          <Button title="Thiết lập nhiệt độ giới hạn" onPress={set_temp_fish} />
        </View>
      </View>
      <View style={{paddingTop:10}}>
        <Button title="Cho cá ăn" onPress={control_eat_fish} />
      </View>
    </View>
  )
};

export default Home;
